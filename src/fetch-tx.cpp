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
#include <sx/serializer/hex.hpp>
#include <sx/utility/callback_args.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static void transaction_fetched(callback_args& args, 
    const transaction_type& tx)
{
    data_chunk bytes(satoshi_raw_size(tx));
    satoshi_save(tx, bytes.begin());
    args.output() << hex(bytes) << std::endl;
    args.stopped() = true;
}

static void handle_callback(callback_args& args, const std::error_code& error,
    const transaction_type& tx, const hash_digest& hash, 
    obelisk::fullnode_interface& fullnode)
{
    const auto handler = [&args](const std::error_code& error, 
        const transaction_type& tx)
    {
        handle_error(args, error);
        transaction_fetched(args, tx);
    };

    // Try the tx memory pool if the transaction is not in the blockchain.
    if (error == error::not_found)
        fullnode.transaction_pool.fetch_transaction(hash, handler);
    else
        handler(error, tx);
}

console_result fetch_tx::invoke(std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto hash = get_hash_argument();

    callback_args args(cerr, output);
    const auto handler = [&args](const std::error_code& error,
        const transaction_type& tx, const hash_digest& hash,
        obelisk::fullnode_interface& fullnode)
    {
        // Don't handle error here since it's needed by the callback.
        handle_callback(args, error, tx, hash, fullnode);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.blockchain.fetch_transaction(hash,
        std::bind(handler, ph::_1, ph::_2, hash, std::ref(fullnode)));
    client.poll(args.stopped());

    return args.result();
}

