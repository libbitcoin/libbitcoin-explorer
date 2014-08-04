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
#include <sx/command/wrap-decode.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

bool split_checksum(const data_chunk& chunk, byte& version, hex& payload,
    hex& checksum)
{
    const size_t version_length = 1;
    const size_t checksum_length = 4;

    // guard against insufficient buffer length
    if (chunk.size() < version_length + checksum_length)
        return false;

    if (!verify_checksum(chunk))
        return false;

    // set return values
    version = chunk.front();
    payload = data_chunk(chunk.begin() + version_length, 
        chunk.end() - checksum_length);
    checksum = data_chunk(chunk.end() - checksum_length, chunk.end());

    return true;
}

// 100% coverage by line, loc ready.
console_result wrap_decode::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const data_chunk hexadecimal = get_hex_argument();

    byte version;
    hex payload, checksum;
    if (!split_checksum(hexadecimal, version, payload, checksum))
    {
        cerr << SX_WRAP_DECODE_INVALID_CHECKSUM << std::endl;
        return console_result::failure;
    }

    output << boost::format(SX_WRAP_DECODE_OUTPUT) % version % payload %
        checksum << std::endl;
    return console_result::okay;
}