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
#include <sx/command/unwrap.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// 100% coverage by line, loc ready.
console_result unwrap::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const data_chunk hex = get_hex_argument();

    // require at least 1 byte of data with a 4 byte checksum
    const size_t minimum_size = 5;

    if (hex.size() < minimum_size)
    {
        cerr << SX_UNWRAP_INVALID_SIZE << std::endl;
        return console_result::failure;
    }

    if (!validate_checksum(hex))
    {
        cerr << SX_UNWRAP_INVALID_CHECKSUM << std::endl;
        return console_result::failure;
    }

    byte version(hex.front());
    bytes data(data_chunk(hex.begin() + 1, hex.end() - 4));
    bytes checksum(data_chunk(hex.end() - 4, hex.end()));

    output << version << " " << data << " " << checksum << std::endl;
    return console_result::okay;
}