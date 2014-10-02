/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
// #include "precompile.hpp"
#include <bitcoin/explorer/commands/fetch-stealth.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/primitives/base2.hpp>
#include <bitcoin/explorer/prop_tree.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

static void handle_error(callback_state& state, const std::error_code& error)
{
    state.handle_error(error);
}

// Write out the transaction hashes of *potential* matches.
static void handle_callback(callback_state& state, 
    const stealth_prefix& prefix, const blockchain::stealth_list& row_list)
{
    state.output(prop_tree(prefix, row_list));
}

static void fetch_stealth_from_prefix(obelisk_client& client,
    callback_state& state, base2 prefix, size_t from_height)
{
    auto on_done = [&state, &prefix](const blockchain::stealth_list& list)
    {
        handle_callback(state, prefix, list);
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    client.get_codec().fetch_stealth(on_error, on_done, prefix, from_height);
}


console_result fetch_stealth::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& prefixes = get_prefixs_argument();
    const auto height = get_height_option();
    const auto& encoding = get_format_option();
    const auto& server = get_server_address_setting();
    const auto retries = get_general_retries_setting();
    const auto timeout = get_general_wait_setting();

    czmqpp::context context;
    obelisk_client client(context, sleep_time(timeout), retries);

    if (client.connect(server) < 0)
        return console_result::failure;

    callback_state state(error, output, encoding);

    for (auto prefix: prefixes)
        fetch_stealth_from_prefix(client, state, prefix, height);

    client.resolve_callbacks();

    return state.get_result();
}

