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
#include <sx/command/fetch-tx.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/callback_state.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/prop_tree.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace obelisk;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static void transaction_fetched(callback_state& state,
    const tx_type& tx)
{
    if (state.get_engine() == encoding_engine::native)
        state.output(transaction(tx));
    else
        state.output(prop_tree(tx));

    // This is always the termination of a call, so decrement.
    --state;
}

static void handle_fetch_callback(callback_state& state, 
    const std::error_code& code, const tx_type& tx, 
    const hash_digest& hash, fullnode_interface& fullnode)
{
    const auto fetched_handler = [&state](const std::error_code& code, 
        const tx_type& tx)
    {
        if (!state.handle_error(code))
            transaction_fetched(state, tx);
    };

    // No state decrement here since we are always forwarding the call.
    // If the transaction is not in the blockchain try the tx memory pool.
    if (code == error::not_found)
        fullnode.transaction_pool.fetch_transaction(hash, fetched_handler);
    else
        fetched_handler(code, tx);
}

// We only serialize a transaction, stealth is relayed if confirmed.
static void handle_prefix_callback(callback_state& state,
    const blockchain::stealth_list& row_list, const ec_secret& secret,
    fullnode_interface& fullnode)
{
    for (const auto& row: row_list)
    {
        const auto& hash = row.transaction_hash;

        // Write out the transaction hashes of *potential* matches.
        // state.output(btc256(row.transaction_hash));

        if (stealth_match(row, secret))
        {
            // Write out the transaction hashes of *actual* matches.
            // state.output(btc256(row.transaction_hash));

            // Hash should not be a reference here, since it changes.
            const auto fetch_handler = [&state, hash, &fullnode](
                const std::error_code& code, const tx_type& tx)
            {
                // Don't handle error here since it's needed by the callback.
                handle_fetch_callback(state, code, tx, hash, fullnode);
            };

            // As we are fanning out against the list we increment for each.
            ++state;

            // If a filtered row matches then chase down the transaction.
            fullnode.transaction_pool.fetch_transaction(hash, fetch_handler);
        }
    }

    // This call has been handled.
    --state;
}

console_result fetch_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto height = get_height_option();
    const auto& hashes = get_hashs_option();
    const auto& prefixes = get_prefixs_option();
    const auto& secret = get_secret_option();
    const auto& encoding = get_format_option();

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    callback_state state(error, output, encoding);

    const auto fetch_handler = [&state](const std::error_code& code,
        const tx_type& tx, const hash_digest& hash,
        fullnode_interface& fullnode)
    {
        // Don't handle error here since it's needed by the callback.
        handle_fetch_callback(state, code, tx, hash, fullnode);
    };

    const auto prefix_handler = [&state, &secret, &fullnode](
        const std::error_code& code,
        const blockchain::stealth_list& stealth_results)
    {
        if (!state.handle_error(code))
            handle_prefix_callback(state, stealth_results, secret, fullnode);
    };

    for (const hash_digest& hash: hashes)
    {
        ++state;
        fullnode.blockchain.fetch_transaction(hash,
            std::bind(fetch_handler, ph::_1, ph::_2, hash, 
                std::ref(fullnode)));
    }

    for (const stealth_prefix& prefix: prefixes)
    {
        ++state;
        fullnode.blockchain.fetch_stealth(prefix,
            std::bind(prefix_handler, ph::_1, ph::_2), height);
    }

    client.poll(state.stopped());

    return state.get_result();
}

