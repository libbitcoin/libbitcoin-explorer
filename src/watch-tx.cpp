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
#include <sx/command/watch-tx.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace obelisk;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static void handle_subscribed(callback_state& state, 
    const worker_uuid& worker)
{
    state.output(SX_WATCH_TX_WAITING);
}

// TODO: use parse tree.
static void handle_update(callback_state& state, size_t height,
    const hash_digest& block_hash, const transaction_type& tx)
{
    state.output(boost::format(SX_WATCH_TX_OUTPUT) % transaction(tx) %
        height % hex(block_hash));
}

// This command only halts on failure.
console_result watch_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    //const auto height = get_height_option();
    //const auto& hashes = get_hashs_option();
    //const hash_digest& hash = hashes.front();
    const auto& prefixes = get_prefixs_option();

    callback_state state(error, output);
    const auto update_handler = [&state](const std::error_code& code,
        size_t height, const hash_digest& block_hash, 
        const transaction_type& tx)
    {
        if (!handle_error(state, code))
            handle_update(state, height, block_hash, tx);
    };

    const auto subscribed_handler = [&state](const std::error_code& code,
        const worker_uuid& worker)
    {
        if (!handle_error(state, code))
            handle_subscribed(state, worker);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    for (const auto& prefix: prefixes)
    {
        ++state;
        fullnode.address.subscribe(prefix, update_handler, subscribed_handler);

        // TODO: need to verify this setup is correct for multiple simo txs.
        break;
    }

    client.poll(state.stopped());

    return state.get_result();
}