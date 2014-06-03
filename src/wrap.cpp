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
#include <sx/command/wrap.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result wrap::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 3))
        return console_result::failure;

    std::string hex_str;
    uint8_t version_byte;
    read_address_tuple(argc, argv, std::cin, hex_str, version_byte);

    data_chunk bytes;
    bytes.push_back(version_byte);
    extend_data(bytes, decode_hex(hex_str));
    uint32_t checksum = bitcoin_checksum(bytes);
    extend_data(bytes, to_little_endian(checksum));

    std::cout << bytes << std::endl;
    return console_result::okay;
}

