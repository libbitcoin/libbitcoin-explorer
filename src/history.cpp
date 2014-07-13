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
#include <boost/format.hpp>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/command/history.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static bool is_first;
static bool json_output;
static std::mutex mutex;
static console_result result;
static size_t remaining_count;
static std::condition_variable condition;

//for (const auto& row: history)
//{
//    std::cout << "Address: " << payaddr.encoded() << std::endl;
//    std::cout << "  output: " << row.output << std::endl;
//    std::cout << "  output_height: ";
//    if (!row.output_height)
//        std::cout << "Pending";
//    else
//        std::cout << row.output_height;
//
//    std::cout << std::endl;
//    std::cout << "  value:  " << row.value << std::endl;
//    if (row.spend.hash == null_hash)
//    {
//        std::cout << "  spend: Unspent" << std::endl;
//        std::cout << "  spend_height: Unspent" << std::endl;
//    }
//    else
//    {
//        std::cout << "  spend: " << row.spend << std::endl;
//        std::cout << "  spend_height: ";
//        if (!row.spend_height)
//            std::cout << "Pending";
//        else
//            std::cout << row.spend_height;
//
//        std::cout << std::endl;
//    }
//
//    std::cout << std::endl;
//}

static void history_fetched(const payment_address& payaddr,
    const std::error_code& error, const blockchain::history_list& history)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        result = console_result::failure;

        std::lock_guard<std::mutex> lock(mutex);
        BITCOIN_ASSERT(remaining_count > 0);
        remaining_count = 0;
        condition.notify_one();
        return;
    }

    //for (const auto& row : history)
    //{
    //    uint64_t total_recieved, balance, pending_balance;
    //    parse_balance_history(balance, pending_balance, total_recieved, history);

    //    // Put commas between each array item in json output.
    //    if (is_first)
    //        is_first = false;
    //    else
    //        std::cout << "," << std::endl;

    //    // Actual row data.
    //    std::cout << "{" << std::endl;
    //    std::cout << "  \"address\": \"" << payaddr.encoded()
    //        << "\"," << std::endl;
    //    std::cout << "  \"output\": \"" << row.output
    //        << "\"," << std::endl;
    //    std::cout << "  \"output_height\": ";
    //    if (!row.output_height)
    //        std::cout << "\"Pending\"";
    //    else
    //        std::cout << row.output_height;

    //    std::cout << "," << std::endl;
    //    std::cout << "  \"value\":  \"" << row.value << "\"," << std::endl;
    //    if (row.spend.hash == null_hash)
    //    {
    //        std::cout << "  \"spend\": \"Unspent\"," << std::endl;
    //        std::cout << "  \"spend_height\": \"Unspent\"" << std::endl;
    //    }
    //    else
    //    {
    //        std::cout << "  \"spend\": \"" << row.spend << "\"," << std::endl;
    //        std::cout << "  \"spend_height\": ";
    //        if (!row.spend_height)
    //            std::cout << "\"Pending\"";
    //        else
    //            std::cout << "\"" << row.spend_height << "\"";
    //    }

    //    std::cout << "}";
    //}
}

// Untestable without fullnode virtualization, loc ready.
console_result history::invoke(std::istream& input, std::ostream& output,
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
            cerr << boost::format(SX_HISTORY_INVALID_ADDRESS) % raw_address
                << std::endl;
            return console_result::failure;
        }

        addresses.push_back(address);
    }

    is_first = true;
    json_output = json;
    result = console_result::okay;
    remaining_count = addresses.size();

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();

    for (const auto& address : addresses)
    {
        fullnode.address.fetch_history(address,
            std::bind(history_fetched, address, std::placeholders::_1,
                std::placeholders::_2));
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

