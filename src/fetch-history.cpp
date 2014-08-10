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
#include "precompile.hpp"
#include <sx/command/fetch-history.hpp>

#include <atomic>
#include <condition_variable>
#include <stdint.h>
#include <thread>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/input.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: use parse tree.
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
// "Address: %1%\n  Output: %2%\n  Output height: %3%\n  Value: %4%\n
// spend: %5%\n  Spend height: %6%"

static pt::ptree parse_tree(const blockchain::history_row& row)
{
    pt::ptree tree;

    // TODO: create row serializer.
    std::string output_height, row_spend, spend_height;

    std::stringstream output_height_stream;
    if (row.output_height == 0)
        output_height_stream << json_pending;
    else
        output_height_stream << row.output_height;
    output_height = output_height_stream.str();

    std::stringstream row_spend_stream;
    if (row.spend.hash == null_hash)
        row_spend_stream << json_unspent;
    else
        row_spend_stream << input(row.spend);
    row_spend = row_spend_stream.str();

    std::stringstream spend_height_stream;
    if (row.spend.hash == null_hash)
        spend_height_stream << json_unspent;
    else if (row.spend_height == 0)
        spend_height_stream << json_pending;
    else
        spend_height_stream << row.spend_height;
    spend_height = spend_height_stream.str();

    return tree;
}

static void handle_callback(callback_state& state,
    const payment_address& pay_address, 
    const blockchain::history_list& history, bool json, bool xml)
{
    // TODO: to keep rows toghether in output requires an external lock here.
    for (const auto& row: history)
    {
        const auto tree = parse_tree(row);

        // TODO: serialize parse tree here as json, xml or info.
        std::string output_height, row_spend, spend_height;
        state.output(format(json_format) % address(pay_address) % row.output %
            output_height % row.value %  row_spend % spend_height);

        --state;
    }
}

// Untestable without fullnode virtualization, loc ready.
console_result fetch_history::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto json = get_json_option();
    const auto xml = false; // get_xml_option();
    const auto& addresses = get_addresss_argument();

    callback_state state(error, output);
    const auto handler = [&state, &json, &xml](const payment_address& address,
        const std::error_code& code, const blockchain::history_list& history)
    {
        // TODO: move json/xml/info switch into callback_state enum.
        if (!handle_error(state, code))
            handle_callback(state, address, history, json, xml);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    for (const auto& address: addresses)
    {
        // TODO: take external lock and set all callbacks before releasing.
        ++state;
        fullnode.address.fetch_history(address,
            std::bind(handler, address, ph::_1, ph::_2));
    }

    client.poll(state.stopped());

    return state.get_result();
}

