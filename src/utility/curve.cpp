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
#include <random>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/curve.hpp>

using namespace bc;

namespace sx {

ec_secret generate_random_secret()
{
    std::random_device random;
    std::default_random_engine engine(random());
    ec_secret secret;
    for (uint8_t& byte : secret)
        byte = engine() % std::numeric_limits<uint8_t>::max();
    return secret;
}

// TODO: move this loc text to consuming method and emit when this is false.
// std::cerr << "sx: Unable to read input values." << std::endl;
bool ec_math_parse_args(const int argc, const char* argv[],
    ec_secret& secret, ec_point& point)
{
    for (int i = 1; i < argc; ++i)
    {
        const auto arg = argv[i];
        if (set_ec_secret(secret, arg))
            continue;
        if (set_ec_point(point, arg))
            continue;
    }

    // NOTE: these values are never set by this function 
    // so it is assumed they are the initial values.
    return (secret != null_hash && !point.empty());
}

bool set_ec_secret(ec_secret& secret, const std::string& arg)
{
    ec_secret result = decode_hash(arg);
    if (result == null_hash)
        return false;
    secret = result;
    return true;
}

bool set_ec_point(ec_point& point, const std::string& arg)
{
    ec_point result = decode_hex(arg);
    if (result.size() != ec_compressed_size)
       return false;
    if (result[0] != 0x02 && result[0] != 0x03)
       return false;
    point = result;
    return true;
}

} // sx