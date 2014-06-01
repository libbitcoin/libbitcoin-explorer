/*
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
#include <sx/utility/client.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

// TODO: this should be a member of sx::extensions::fetch_block_header,
// otherwise concurrent test execution will collide on shared state.
bool fetch_block_header_stopped = false;

// TODO: fetch_block_header_stopped should be passed here via closure
// or by converting this to a member function.
void block_header_fetched(const std::error_code& ec,
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

    fetch_block_header_stopped = true;
}

// Try first to interpret the index as a hash, otherwise treat it as a height.
bool initialize_fetch_block_header(std::string& index, 
    obelisk::fullnode_interface& fullnode)
{
    size_t height;
    hash_digest hash(decode_hash(index));

    if (hash != null_hash)
        fullnode.blockchain.fetch_block_header(hash, block_header_fetched);
    else if (sx::parse<size_t>(index, height))
        fullnode.blockchain.fetch_block_header(height, block_header_fetched);
    else
        return false;

    return true;
}

bool sx::extensions::fetch_block_header::invoke(const int argc,
    const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return false;

    std::string index(argc == 1 ? read_stdin() : argv[1]);

    OBELISK_FULLNODE(pool, fullnode);
    if (!initialize_fetch_block_header(index, fullnode))
    {
        line_out(std::cerr, "fetch-block-header: Bad index provided.");
        return false;
    }
    poll(fullnode, pool, fetch_block_header_stopped);

    return true;
}

