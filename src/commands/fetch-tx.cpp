/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitcoin/explorer/commands/fetch-tx.hpp>

#include <iostream>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/config/transaction.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::client;
using namespace bc::explorer::config;

console_result fetch_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto witness = get_witness_option();
    const auto& hash = get_hash_argument();
    const auto connection = get_connection(*this);

    obelisk_client client(connection);

    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    // This enables json-style array formatting.
    const auto json = encoding == encoding_engine::json;

    auto on_done = [&state, json](const tx_type& tx)
    {
        state.output(prop_tree(tx, json));
    };

    auto on_error = [&state](const code& error)
    {
        state.succeeded(error);
    };

    if (witness)
        client.transaction_pool_fetch_transaction2(on_error, on_done, hash);
    else
        client.transaction_pool_fetch_transaction(on_error, on_done, hash);

    client.wait();

    return state.get_result();
}


} //namespace commands
} //namespace explorer
} //namespace libbitcoin
