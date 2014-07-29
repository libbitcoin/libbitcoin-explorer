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
#include <sx/define.hpp>
#include <sx/dispatch.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/serializer/address.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// This is NOT localizable.
static const char* json_format =
    "{\n"
    "   \"address\": \"%1%\",\n"
    "   \"paid\": \"%2%\",\n"
    "   \"pending\": \"%3%\",\n"
    "   \"received\": \"%4%\"\n"
    "}";

static bool json_output;
static bool first_address;
static std::mutex mutex;
static console_result result;
static size_t remaining_count;
static std::condition_variable condition;

static void parse_balance_history(uint64_t& balance, uint64_t& pending_balance,
    uint64_t& total_recieved, const blockchain::history_list& history)
{
    balance = 0;
    pending_balance = 0;
    total_recieved = 0;

    for (const auto& row : history)
    {
        auto value = row.value;
        BITCOIN_ASSERT(value >= 0);
        total_recieved += value;

        // Unconfirmed balance.
        if (row.spend.hash == null_hash)
            pending_balance += value;

        // Confirmed balance.
        if (row.output_height &&
            (row.spend.hash == null_hash || !row.spend_height))
            balance += value;

        BITCOIN_ASSERT(balance < total_recieved);
        BITCOIN_ASSERT(pending_balance < total_recieved);
    }
}

// TODO: for testability parameterize STDOUT and STDERR.
// TODO: use json serializer and generalize to all command outputs.
static void balance_fetched(const payment_address& pay_address,
    const std::error_code& error, const blockchain::history_list& history)
{
    std::lock_guard<std::mutex> lock(mutex);
    BITCOIN_ASSERT(remaining_count > 0);

    if (error)
    {
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
        remaining_count = 0;
        condition.notify_one();
        return;
    }

    uint64_t total_recieved, balance, pending_balance;
    parse_balance_history(balance, pending_balance, total_recieved, history);

    if (json_output && first_address)
        std::cout << "[" << std::endl;

    if (first_address)
        first_address = false;

    auto format = if_else(json_output, json_format, SX_BALANCE_OUTPUT);

    std::cout << boost::format(format) % address(pay_address) % balance %
        pending_balance % total_recieved;

    if (json_output)
    {
        if (remaining_count > 0)
            std::cout << "," << std::endl;
        else
            std::cout << "]" << std::endl;
    }

    --remaining_count;
    condition.notify_one();
}

// Untestable without fullnode virtualization, loc ready.
console_result balance::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    // TODO: improve generated property pluralization.
    auto addresses = get_addresss_argument();
    const auto json = get_json_option();

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

    json_output = json;
    first_address = true;
    result = console_result::okay;
    remaining_count = addresses.size();

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();

    for (const auto& address: addresses)
    {
        fullnode.address.fetch_history(address,
            std::bind(balance_fetched, address, ph::_1, ph::_2));
    }

    bool done = false;
    client.detached_poll(done);

    std::unique_lock<std::mutex> lock(mutex);
    while (remaining_count > 0)
        condition.wait(lock);

    client.stop();
    done = true;

    return result;
}