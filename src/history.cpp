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
#include <sx/serializer/address.hpp>
#include <sx/serializer/point.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// These are NOT localizable.
static const char* json_pending = "pending";
static const char* json_unspent = "unspent";
static const char* json_format = \
    "{\n"
    "   \"address\": \"%1%\",\n"
    "   \"output\": \"%2%\",\n"
    "   \"output_height\": \"%3%\",\n"
    "   \"value\": \"%4%\",\n"
    "   \"spend\": \"%5%\",\n"
    "   \"spend_height\": \"%6%\"\n"
    "}";

static bool json_output;
static bool first_address;
static std::mutex mutex;
static console_result result;
static size_t remaining_count;
static std::condition_variable condition;

static void parse_history(std::string& output_height, std::string& row_spend,
    std::string& spend_height, const blockchain::history_row& row, bool json)
{
    auto pending = if_else(json, json_pending, SX_HISTORY_PENDING);
    auto unspent = if_else(json, json_unspent, SX_HISTORY_UNSPENT);

    std::stringstream output_height_stream;
    if (row.output_height == 0)
        output_height_stream << pending;
    else
        output_height_stream << row.output_height;
    output_height = output_height_stream.str();

    std::stringstream row_spend_stream;
    if (row.spend.hash == null_hash)
        row_spend_stream << unspent;
    else
        row_spend_stream << point(row.spend);
    row_spend = row_spend_stream.str();

    std::stringstream spend_height_stream;
    if (row.spend.hash == null_hash)
        spend_height_stream << unspent;
    else if (row.spend_height == 0)
        spend_height_stream << pending;
    else
        spend_height_stream << row.spend_height;
    spend_height = spend_height_stream.str();
}

// TODO: for testability parameterize STDOUT and STDERR.
static void history_fetched(const payment_address& pay_address,
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

    auto format = if_else(json_output, json_format, SX_HISTORY_OUTPUT);

    if (json_output)
    {
        if (first_address)
            std::cout << "[" << std::endl;
        else
            first_address = false;
    }

    bool first_row = true;
    for (const auto& row : history)
    {
        if (json_output)
        {
            if (first_row)
                first_row = false;
            else
                std::cout << "," << std::endl;
        }

        std::string output_height;
        std::string row_spend;
        std::string spend_height;
        parse_history(output_height, row_spend, spend_height, row,
            json_output);

        std::cout << boost::format(format) % address(pay_address) % 
            row.output % output_height % row.value %  row_spend % spend_height;
    }

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

    json_output = json;
    first_address = true;
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

