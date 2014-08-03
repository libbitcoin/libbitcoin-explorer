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
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: this should be a member of sx::extensions::fetch_header_hash,
// otherwise concurrent test execution will collide on shared state.
static bool stopped;
static console_result result;

// TODO: stopped should be passed here via closure
// or by converting this to a member function.
static void hash_header_fetched(const std::error_code& error,
    const block_header_type& block_header)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
    }
    else
    {
        data_chunk raw_block_header(satoshi_raw_size(block_header));
        satoshi_save(block_header, raw_block_header.begin());
        std::cout << hex(raw_block_header) << std::endl;
    }

    stopped = true;
}

// TODO: stopped should be passed here via closure
// or by converting this to a member function.
static void height_header_fetched(const std::error_code& error,
    const block_header_type& block_header)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
    }
    else
    {
        data_chunk raw_block_header(satoshi_raw_size(block_header));
        satoshi_save(block_header, raw_block_header.begin());
        std::cout << hex(raw_block_header) << std::endl;
    }

    stopped = true;
}

console_result fetch_header::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const size_t height = get_height_option();
    const hash_digest hash = get_hash_option();

    stopped = false;
    result = console_result::okay;

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();

    if (hash == null_hash)
        fullnode.blockchain.fetch_block_header(height, height_header_fetched);
    else
        fullnode.blockchain.fetch_block_header(hash, hash_header_fetched);

    client.poll(stopped);

    return result;
}

