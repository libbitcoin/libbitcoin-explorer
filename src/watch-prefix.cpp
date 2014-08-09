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
#include <sx/command/watch-prefix.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: consolidate as watch-tx [prefix].

static void handle_subscribed(callback_args& args, 
    const obelisk::worker_uuid& worker)
{
    args.output() << SX_WATCH_PREFIX_WAITING << std::endl;
}

static void handle_update(callback_args& args, size_t height,
    const hash_digest& block_hash, const transaction_type& tx)
{
    args.output() << boost::format(SX_WATCH_PREFIX_OUTPUT) % transaction(tx) %
        height % hex(block_hash) << std::endl;
}

// This command only halts on failure.
console_result watch_prefix::invoke(std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    //const auto height = get_height_option();
    const stealth_prefix prefix = get_prefix_option();

    callback_args args(cerr, output);
    const auto update_handler = [&args](const std::error_code& error,
        size_t height, const hash_digest& block_hash, 
        const transaction_type& tx)
    {
        handle_error(args, error);
        handle_update(args, height, block_hash, tx);
    };

    const auto subscribed_handler = [&args](const std::error_code& error,
        const obelisk::worker_uuid& worker)
    {
        handle_error(args, error);
        handle_subscribed(args, worker);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.address.subscribe(prefix, update_handler, subscribed_handler);
    client.poll(args.stopped());

    return args.result();
}

