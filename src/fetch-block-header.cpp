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
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/command/fetch-block-header.hpp>
#include <sx/obelisk.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

// TODO: this should be a member of sx::extensions::fetch_block_header,
// otherwise concurrent test execution will collide on shared state.
static bool node_stopped = false;

// TODO: node_stopped should be passed here via closure
// or by converting this to a member function.
static void block_header_fetched(const std::error_code& ec,
    const block_header_type& blk_header)
{
    if (ec)
        std::cerr << "fetch-block-header: " << ec.message() << std::endl;
    else
    {
        data_chunk raw_blk_header(satoshi_raw_size(blk_header));
        satoshi_save(blk_header, raw_blk_header.begin());
        std::cout << raw_blk_header << std::endl;
    }

    node_stopped = true;
}

// Try first to interpret the index as a hash, otherwise treat it as a height.
static bool initialize_fetch_block_header(std::string& index,
    obelisk::fullnode_interface& fullnode)
{
    size_t height;
    hash_digest hash(decode_hash(index));

    if (hash != null_hash)
        fullnode.blockchain.fetch_block_header(hash, block_header_fetched);
    else if (parse<size_t>(index, height))
        fullnode.blockchain.fetch_block_header(height, block_header_fetched);
    else
        return false;

    return true;
}

console_result fetch_block_header::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return console_result::failure;

    std::string index(get_arg_or_stream(argc, argv, std::cin));

    OBELISK_FULLNODE(pool, fullnode);
    if (!initialize_fetch_block_header(index, fullnode))
    {
        line_out(std::cerr, "fetch-block-header: Bad index provided.");
        return console_result::failure;
    }
    poll(fullnode, pool, node_stopped);

    return console_result::okay;
}

