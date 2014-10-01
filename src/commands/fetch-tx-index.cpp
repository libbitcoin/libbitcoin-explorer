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
#include <bitcoin/explorer/commands/fetch-tx-index.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
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

static void handle_callback(callback_state& state, const hash_digest& hash,
    size_t height, size_t index)
{
    if (state.get_engine() == encoding_engine::native)
        state.output(boost::format(BX_FETCH_TX_INDEX_OUTPUT) % base16(hash) % 
            height % index);
    else
        state.output(prop_tree(hash, height, index));
}

static void fetch_tx_index_from_hash(obelisk_client& client,
    callback_state& state, const primitives::btc256& hash)
{
    // Do not pass the hash by reference here.
    auto on_done = [&state, hash](size_t block_height, size_t index)
    {
        handle_callback(state, hash, block_height, index);
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    client.get_codec().fetch_transaction_index(on_error, on_done, hash);
}

console_result fetch_tx_index::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& hashes = get_hashs_argument();
    const auto retries = get_general_retries_setting();
    const auto timeout = get_general_wait_setting();
    const auto& server = get_server_address_setting();

    czmqpp::context context;
    obelisk_client client(context, sleep_time(timeout), retries);

    if (client.connect(server) < 0)
        return console_result::failure;

    callback_state state(error, output, encoding);

    for (auto hash: hashes)
        fetch_tx_index_from_hash(client, state, hash);

    client.resolve_callbacks();

    return state.get_result();
}

