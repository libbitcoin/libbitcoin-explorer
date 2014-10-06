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
#include <bitcoin/explorer/commands/fetch-history.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
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

static void handle_callback(callback_state& state,
    const payment_address& address, const std::vector<history_row>& histories)
{
    // native is info.
    state.output(prop_tree(address, histories));
}

static void fetch_history_from_address(obelisk_client& client,
    callback_state& state, const primitives::address& address)
{
    // Do not pass the address by reference here.
    auto on_done = [&state, address](const blockchain::history_list& list)
    {
        handle_callback(state, address, list);
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    client.get_codec()->fetch_history(on_error, on_done, address);
}

// When you restore your wallet, you should use fetch_history(). 
// But for updating the wallet, use the [new] scan() method- 
// which is faster because you avoid pulling the entire history.
// We can eventually increase privacy and performance (fewer calls to scan())
// by 'mining' addresses with the same prefix, allowing us to fetch the 
// prefix group. Obelisk will eventually support privacy enhanced history for 
// address scan by prefix.
console_result fetch_history::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& addresses = get_bitcoin_addresss_argument();
    const auto retries = get_general_retries_setting();
    const auto timeout = get_general_wait_setting();
    const auto& server = get_server_address_setting();

    czmqpp::context context;
    obelisk_client client(context, period_ms(timeout), retries);

    if (client.connect(server) < 0)
        return console_result::failure;

    callback_state state(error, output, encoding);

    for (auto address: addresses)
        fetch_history_from_address(client, state, address);

    client.resolve_callbacks();

    return state.get_result();
}

