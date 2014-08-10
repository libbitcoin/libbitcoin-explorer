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
static const char* json_format =
    "{\n"
    "   \"address\": \"%1%\",\n"
    "   \"paid\": \"%2%\",\n"
    "   \"pending\": \"%3%\",\n"
    "   \"received\": \"%4%\"\n"
    "}";
// "Address: %1%\n  Paid balance:    %2%\n  Pending 
// balance: %3%\n  Total received:  %4%"

// Do not assert against server response values.
//BITCOIN_ASSERT(value >= 0);
//BITCOIN_ASSERT(balance < total_recieved);
//BITCOIN_ASSERT(pending_balance < total_recieved);
static pt::ptree parse_tree(const blockchain::history_list& history)
{
    pt::ptree tree;

    // TODO: create history serializer that summarizes rows.
    uint64_t total_recieved(0), balance(0), pending_balance(0);

    for (const auto& row : history)
    {
        auto value = row.value;
        total_recieved += value;

        // Unconfirmed balance.
        if (row.spend.hash == null_hash)
            pending_balance += value;

        // Confirmed balance.
        if (row.output_height &&
            (row.spend.hash == null_hash || !row.spend_height))
            balance += value;
    }

    return tree;
}

static void handle_callback(callback_state& state, 
    const payment_address& pay_address,
    const blockchain::history_list& history, bool json, bool xml)
{
    const auto tree = parse_tree(history);

    // TODO: serialize parse tree here as json, xml or info.
    uint64_t total_recieved, balance, pending_balance;
    state.output(format(json_format) % address(pay_address) % balance %
        pending_balance % total_recieved);

    --state;
}

// Untestable without fullnode virtualization, loc ready.
console_result fetch_balance::invoke(std::ostream& output, std::ostream& error)
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