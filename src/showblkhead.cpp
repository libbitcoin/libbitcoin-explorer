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
#include <sx/command/showblkhead.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result showblkhead::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return console_result::failure;

    block_header_type blk_header;
    std::string filename(get_filename(argc, argv));
    if (!load_satoshi_item<block_header_type>(blk_header, filename, std::cin))
    {
        std::cerr << "sx: Deserializing block header failed." << std::endl;
        return console_result::failure;
    }

    // Show details.
    std::cout << "hash: " << hash_block_header(blk_header) << std::endl;
    std::cout << "version: " << blk_header.version << std::endl;
    std::cout << "previous_block_hash: "
        << blk_header.previous_block_hash << std::endl;
    std::cout << "merkle: " << blk_header.merkle << std::endl;
    std::cout << "timestamp: " << blk_header.timestamp << std::endl;
    std::cout << "bits: " << blk_header.bits << std::endl;
    std::cout << "nonce: " << blk_header.nonce << std::endl;
    return console_result::okay;
}