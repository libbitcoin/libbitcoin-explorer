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

#include <bitcoin/explorer/commands/fetch-tx.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/primitives/btc256.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

static void handle_error(callback_state& state, const std::error_code& error)
{
    state.handle_error(error);
}

static void handle_callback(callback_state& state, const tx_type& tx)
{
    state.output(prop_tree(tx));
}

static void fetch_tx_from_hash(obelisk_client& client, callback_state& state,
    btc256 hash)
{
    auto on_done = [&state](const tx_type& tx)
    {
        handle_callback(state, tx);
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    client.get_codec()->fetch_transaction(on_error, on_done, hash);
}

console_result fetch_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& hash = get_hash_argument();
    const auto retries = get_general_retries_setting();
    const auto timeout = get_general_wait_setting();
    const auto& server = if_else(get_general_network_setting() == "testnet",
        get_testnet_url_setting(), get_mainnet_url_setting());

    czmqpp::context context;
    obelisk_client client(context, period_ms(timeout), retries);

    if (client.connect(server) < 0)
        return console_result::failure;

    callback_state state(error, output, encoding);
    fetch_tx_from_hash(client, state, hash);
    client.resolve_callbacks();

    return state.get_result();
}

