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
#include <sx/command/fetch-header.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/utility/callback_args.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static void handle_callback(callback_args& args, const block_header_type& block_header)
{
    data_chunk bytes(satoshi_raw_size(block_header));
    satoshi_save(block_header, bytes.begin());
    args.output() << hex(bytes) << std::endl;
    args.stopped() = true;
}

console_result fetch_header::invoke(std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const size_t height = get_height_option();
    const hash_digest hash = get_hash_option();

    callback_args args(cerr, output);
    const auto handler = [&args](const std::error_code& error,
        const block_header_type& block_header)
    {
        handle_error(args, error);
        handle_callback(args, block_header);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    if (hash == null_hash)
        fullnode.blockchain.fetch_block_header(height, handler);
    else
        fullnode.blockchain.fetch_block_header(hash, handler);
    client.poll(args.stopped());

    return args.result();
}

