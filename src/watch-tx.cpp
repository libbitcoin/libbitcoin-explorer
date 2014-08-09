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

static void handle_subscribed(callback_args& args, 
    const worker_uuid& worker)
{
    args.output() << SX_WATCH_TX_WAITING << std::endl;
}

// TODO: use parse tree.
static void handle_update(callback_args& args, size_t height,
    const hash_digest& block_hash, const transaction_type& tx)
{
    args.output() << boost::format(SX_WATCH_TX_OUTPUT) % transaction(tx) %
        height % hex(block_hash) << std::endl;
}

// This command only halts on failure.
console_result watch_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    //const auto height = get_height_option();
    //const auto& hashes = get_hashs_option();
    //const hash_digest& hash = hashes.front();
    const auto& prefixes = get_prefixs_option();

    callback_args args(error, output);
    const auto update_handler = [&args](const std::error_code& code,
        size_t height, const hash_digest& block_hash, 
        const transaction_type& tx)
    {
        handle_error(args, code);
        handle_update(args, height, block_hash, tx);
    };

    const auto subscribed_handler = [&args](const std::error_code& code,
        const worker_uuid& worker)
    {
        handle_error(args, code);
        handle_subscribed(args, worker);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();

    // Create a subscription for each prefix.
    for (const auto& prefix: prefixes)
        fullnode.address.subscribe(prefix, update_handler, subscribed_handler);

    client.poll(args.stopped());

    return args.result();
}