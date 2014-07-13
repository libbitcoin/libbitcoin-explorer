/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <sx/command/balance.hpp>

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <stdint.h>
#include <thread>
//#include <sstream>
#include <boost/format.hpp>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/dispatch.hpp>
#include <sx/obelisk.hpp>
#include <sx/serializer/address.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static bool is_first;
static std::mutex mutex;
static size_t remaining_count = 0;
static std::condition_variable condition;
static console_result result = console_result::okay;

static void parse_history(uint64_t& balance, uint64_t& pending_balance,
    uint64_t& total_recieved, const blockchain::history_list& history)
{
    balance = 0;
    pending_balance = 0;
    total_recieved = 0;

    for (const auto& row: history)
    {
        uint64_t value = row.value;
        BITCOIN_ASSERT(value >= 0);
        total_recieved += value;

        // Unconfirmed balance.
        if (row.spend.hash == null_hash)
            pending_balance += value;

        // Confirmed balance.
        if (row.output_height &&
            (row.spend.hash == null_hash || !row.spend_height))
            balance += value;

        BITCOIN_ASSERT(total_recieved >= balance);
        BITCOIN_ASSERT(total_recieved >= pending_balance);
    }
}

// TODO: for testability parameterize STDOUT and STDERR.
static void balance_fetched(const payment_address& payaddr,
    const std::error_code& error, const blockchain::history_list& history)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        remaining_count = 0;
        result = console_result::failure;
        return;
    }

    uint64_t total_recieved, balance, pending_balance;
    parse_history(balance, pending_balance, total_recieved, history);

    std::cout << boost::format(SX_BALANCE_FETCHED_TEXT_OUTPUT) % 
        payaddr.encoded() % balance % pending_balance % total_recieved;

    std::lock_guard<std::mutex> lock(mutex);
    BITCOIN_ASSERT(remaining_count > 0);
    --remaining_count;
    condition.notify_one();
}

// TODO: use json serializer.
// TODO: for testability parameterize STDOUT and STDERR.
static void json_balance_fetched(const payment_address& payaddr,
    const std::error_code& error, const blockchain::history_list& history)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        remaining_count = 0;
        result = console_result::failure;
        return;
    }

    uint64_t total_recieved, balance, pending_balance;
    parse_history(balance, pending_balance, total_recieved, history);

    if (is_first)
        std::cout << "[" << std::endl;

    std::cout << boost::format(SX_BALANCE_FETCHED_JSON_OUTPUT) %
        payaddr.encoded() % balance % pending_balance % total_recieved;

    std::lock_guard<std::mutex> lock(mutex);
    BITCOIN_ASSERT(remaining_count > 0);
    --remaining_count;
    condition.notify_one();

    if (remaining_count > 0)
        std::cout << "," << std::endl;
    else
        std::cout << "]" << std::endl;
}

// Untestable without server isolation, loc ready.
console_result balance::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    // TODO: improve generated property pluralization.
    auto addresses = get_addresss_argument();
    auto json = get_json_option();

    // TODO: implement support for defaulting a collection ARG to STDIN.
    if (addresses.empty())
    {
        address address;
        std::string raw_address(read_stream(input));
        if (!address.data().set_encoded(raw_address))
        {
            cerr << boost::format(SX_BALANCE_INVALID_ADDRESS) % raw_address
                << std::endl;
            return console_result::failure;
        }

        addresses.push_back(address);
    }

    OBELISK_FULLNODE(pool, fullnode);

    is_first = true;
    for (const auto& address: addresses)
    {
        if (json)
            fullnode.address.fetch_history(address,
                std::bind(json_balance_fetched, address, 
                    std::placeholders::_1, std::placeholders::_2));
        else
            fullnode.address.fetch_history(address,
                std::bind(balance_fetched, address, 
                    std::placeholders::_1, std::placeholders::_2));
    }

    std::thread update_loop([&fullnode]
    {
        while (true)
        {
            fullnode.update();
            sleep_ms(100);
        }
    });
    update_loop.detach();

    std::unique_lock<std::mutex> lock(mutex);
    remaining_count = addresses.size();
    while (remaining_count > 0)
    {
        condition.wait(lock);
        BITCOIN_ASSERT(remaining_count >= 0);
    }

    pool.stop();
    pool.join();
    return result;
}

