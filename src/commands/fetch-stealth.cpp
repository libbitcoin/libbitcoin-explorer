/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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

#include <bitcoin/explorer/commands/fetch-stealth.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/primitives/base2.hpp>
#include <bitcoin/explorer/prop_tree.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

static bc::client::stealth_prefix get_prefix(const bitset& source)
{
    // Size is constrained by BX_FETCH_STEALTH_PREFIX_TOO_LONG below.
    BITCOIN_ASSERT(source.size() <= stealth_address::max_prefix_bits);

    bc::client::stealth_prefix prefix;
    prefix.number_bits = static_cast<uint8_t>(source.size());
    prefix.bitfield = source.to_ulong();
    return prefix;
}

static void handle_error(callback_state& state, const std::error_code& error)
{
    state.handle_error(error);
}

// Write out the transaction hashes of *potential* matches.
static void handle_callback(callback_state& state,
    const bc::stealth_prefix& prefix,
    const client::stealth_list& row_list)
{
    state.output(prop_tree(row_list));
}

static void fetch_stealth_from_prefix(obelisk_client& client,
    callback_state& state, const base2& prefix, size_t from_height)
{
    // Do not pass the prefix by reference here.
    auto on_done = [&state, prefix](const client::stealth_list& list)
    {
        handle_callback(state, prefix, list);
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    auto query_prefix = get_prefix(prefix);
    client.get_codec()->fetch_stealth(on_error, on_done, query_prefix, from_height);
}

console_result fetch_stealth::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto retries = get_general_retries_setting();
    const auto timeout = get_general_wait_setting();
    const auto height = get_height_option();
    const auto& encoding = get_format_option();
    const stealth_prefix& prefix = get_prefix_argument();
    const auto& server = if_else(get_general_network_setting() == "testnet",
        get_testnet_url_setting(), get_mainnet_url_setting());

    czmqpp::context context;
    obelisk_client client(context, period_ms(timeout), retries);

    if (client.connect(server) < 0)
    {
        display_connection_failure(error, server);
        return console_result::failure;
    }

    if (prefix.size() > stealth_address::max_prefix_bits)
    {
        error << BX_FETCH_STEALTH_PREFIX_TOO_LONG << std::endl;
        return console_result::failure;
    }

    callback_state state(error, output, encoding);
    fetch_stealth_from_prefix(client, state, prefix, height);
    client.resolve_callbacks();

    return state.get_result();
}
