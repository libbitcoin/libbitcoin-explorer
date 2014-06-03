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
#include <atomic>
#include <condition_variable>
#include <stdint.h>
#include <thread>
//#include <sstream>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/command/history.hpp>
#include <sx/utility/client.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/dispatch.hpp>

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

static int32_t remaining_count = bc::max_int32;
static std::mutex mutex;
static std::condition_variable condition;
static bool json_output = false;

static void history_fetched(const payment_address& payaddr,
    const std::error_code& ec, const blockchain::history_list& history)
{
    if (ec)
    {
        std::cerr << "history: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    for (const auto& row: history)
    {
        std::cout << "Address: " << payaddr.encoded() << std::endl;
        std::cout << "  output: " << row.output << std::endl;
        std::cout << "  output_height: ";
        if (!row.output_height)
            std::cout << "Pending";
        else
            std::cout << row.output_height;
        std::cout << std::endl;
        std::cout << "  value:  " << row.value << std::endl;
        if (row.spend.hash == null_hash)
        {
            std::cout << "  spend: Unspent" << std::endl;
            std::cout << "  spend_height: Unspent" << std::endl;
        }
        else
        {
            std::cout << "  spend: " << row.spend << std::endl;
            std::cout << "  spend_height: ";
            if (!row.spend_height)
                std::cout << "Pending";
            else
                std::cout << row.spend_height;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::lock_guard<std::mutex> lock(mutex);
    BITCOIN_ASSERT(remaining_count != bc::max_int32);
    --remaining_count;
    condition.notify_one();
}

// TODO: generalize json serialization.
static void json_history_fetched(const payment_address& payaddr,
    const std::error_code& ec, const blockchain::history_list& history)
{
    if (ec)
    {
        std::cerr << "history: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    bool is_first = true;
    for (const auto& row: history)
    {
        // Put commas between each array item in json output.
        if (is_first)
            is_first = false;
        else
            std::cout << "," << std::endl;

        // Actual row data.
        std::cout << "{" << std::endl;
        std::cout << "  \"address\": \"" << payaddr.encoded()
            << "\"," << std::endl;
        std::cout << "  \"output\": \"" << row.output
            << "\"," << std::endl;
        std::cout << "  \"output_height\": ";
        if (!row.output_height)
            std::cout << "\"Pending\"";
        else
            std::cout << row.output_height;
        std::cout << "," << std::endl;
        std::cout << "  \"value\":  \"" << row.value << "\"," << std::endl;
        if (row.spend.hash == null_hash)
        {
            std::cout << "  \"spend\": \"Unspent\"," << std::endl;
            std::cout << "  \"spend_height\": \"Unspent\"" << std::endl;
        }
        else
        {
            std::cout << "  \"spend\": \"" << row.spend << "\"," << std::endl;
            std::cout << "  \"spend_height\": ";
            if (!row.spend_height)
                std::cout << "\"Pending\"";
            else
                std::cout << "\"" << row.spend_height << "\"";
        }
        std::cout << "}";
    }
    std::lock_guard<std::mutex> lock(mutex);
    BITCOIN_ASSERT(remaining_count != bc::max_int32);
    --remaining_count;
    condition.notify_one();
    if (remaining_count > 0)
        std::cout << ",";
    std::cout << std::endl;
}

bool sx::extensions::history::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1))
        return false;

    // TODO: create generalized and shared aguments class that:
    // * sets all arguments to a string list by position
    // * sets all options arguments to a distinct list
    // * returns the number of non option arguments
    // * returns each argument by positional index
    // * returns each option as a bool by textual index
    // * generic allows any argument to be read with cast to type
    // * passed in to each extension, removing access to argc/argv
    // This will provide for easy faking of arguments for unit testing
    // and greatly rationalize and simplify command line parsing
    // across the multitude of command handlers.
    json_output = get_option(argc, argv, SX_OPTION_JSON);

    payaddr_list payaddrs;
    if (argc == 1)
    {
        payment_address payaddr;
        if (!payaddr.set_encoded(read_stream(std::cin)))
        {
            std::cerr << "history: Invalid address." << std::endl;
            return false;
        }
        payaddrs.push_back(payaddr);
    }
    else if (!read_addresses(argc, argv, payaddrs))
    {
        std::cerr << "history: Invalid address." << std::endl;
        return false;
    }

    remaining_count = static_cast<int>(payaddrs.size());

    OBELISK_FULLNODE(pool, fullnode);

    if (json_output)
        std::cout << "[" << std::endl;
    for (const payment_address& payaddr: payaddrs)
    {
        if (json_output)
            fullnode.address.fetch_history(payaddr,
                std::bind(json_history_fetched, payaddr, _1, _2));
        else
            fullnode.address.fetch_history(payaddr,
                std::bind(history_fetched, payaddr, _1, _2));
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
    while (remaining_count > 0)
    {
        condition.wait(lock);
        BITCOIN_ASSERT(remaining_count >= 0);
    }
    if (json_output)
        std::cout << "]" << std::endl;
    pool.stop();
    pool.join();
    return true;
}

