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
#include <sx/command/fetch-tx.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/btc256.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/utility/callback_args.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace obelisk;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: use parse tree.
static void handle_prefix_callback(callback_args& args,
    const blockchain::stealth_list& stealth_results)
{
    for (const auto& row: stealth_results)
        args.output() << boost::format(SX_FETCH_TX_OUTPUT) %
            hex(row.ephemkey) % address(row.address) %
            btc256(row.transaction_hash) << std::endl;

    // BUGBUG: there is a race condition for termination among callbacks.
    args.stopped() = true;
}

// TODO: use parse tree with missing nodes from stealth.
static void transaction_fetched(callback_args& args, 
    const transaction_type& tx)
{
    args.output() << transaction(tx) << std::endl;

    // BUGBUG: there is a race condition for termination among callbacks.
    args.stopped() = true;
}

static void handle_fetch_callback(callback_args& args, 
    const std::error_code& code, const transaction_type& tx, 
    const hash_digest& hash, fullnode_interface& fullnode)
{
    const auto fetched_handler = [&args](const std::error_code& code, 
        const transaction_type& tx)
    {
        handle_error(args, code);
        transaction_fetched(args, tx);
    };

    // Try the tx memory pool if the transaction is not in the blockchain.
    if (code == error::not_found)
        fullnode.transaction_pool.fetch_transaction(hash, fetched_handler);
    else
        fetched_handler(code, tx);
}

console_result fetch_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto height = get_height_option();
    const auto& hashes = get_hashs_option();
    const auto& prefixes = get_prefixs_option();

    callback_args args(error, output);

    const auto fetch_handler = [&args](const std::error_code& code,
        const transaction_type& tx, const hash_digest& hash, 
        fullnode_interface& fullnode)
    {
        // Don't handle error here since it's needed by the callback.
        handle_fetch_callback(args, code, tx, hash, fullnode);
    };

    const auto prefix_handler = [&args](const std::error_code& code,
        const blockchain::stealth_list& stealth_results)
    {
        handle_error(args, code);
        handle_prefix_callback(args, stealth_results);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();

    for (const hash_digest& hash: hashes)
        fullnode.blockchain.fetch_transaction(hash,
            std::bind(fetch_handler, ph::_1, ph::_2, hash, 
                std::ref(fullnode)));

    for (const stealth_prefix& prefix: prefixes)
        fullnode.blockchain.fetch_stealth(prefix,
            std::bind(prefix_handler, ph::_1, ph::_2), height);

    client.poll(args.stopped());

    return args.result();
}

