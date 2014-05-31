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
#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include <sx/command/base58_encode.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

bool sx::extensions::base58_encode::invoke(const int argc, const char* argv[])
{
    std::string hex_str;
    if (argc == 1) {
        hex_str = sx::read_stdin();
    }
    else if (argc == 2) 
    {
        hex_str = argv[1];
    }
    data_chunk data = decode_hex(hex_str);
    std::cout << encode_base58(data) << std::endl;
    return true;
}

