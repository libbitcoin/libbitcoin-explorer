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
#include <sx/command/fetch-balance.hpp>

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <stdint.h>
#include <thread>
#include <boost/format.hpp>
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

// TODO: use parse tree.
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

static void balance_fetched(const payment_address& pay_address,
    const std::error_code& code, const blockchain::history_list& history)
{
    std::lock_guard<std::mutex> lock(mutex);
    BITCOIN_ASSERT(remaining_count > 0);

    if (code)
    {
        std::cerr << code.message() << std::endl;
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

    auto format = if_else(json_output, json_format, SX_FETCH_BALANCE_OUTPUT);

    std::cout << boost::format(format) % address(pay_address) % balance %
        pending_balance % total_recieved << std::endl;

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
console_result fetch_balance::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto json = get_json_option();
    const auto& addresses = get_addresss_argument();

    json_output = json;
    first_address = true;
    result = console_result::okay;
    remaining_count = addresses.size();

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();

    for (const auto& address: addresses)
        fullnode.address.fetch_history(address,
            std::bind(balance_fetched, address, ph::_1, ph::_2));

    bool done = false;
    client.detached_poll(done);

    std::unique_lock<std::mutex> lock(mutex);
    while (remaining_count > 0)
        condition.wait(lock);

    client.stop();
    done = true;

    return result;
}