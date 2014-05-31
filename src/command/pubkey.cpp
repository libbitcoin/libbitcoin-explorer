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
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    if (argc > 2)
    {
        std::cerr << "Usage: sx pubkey [--uncompressed|--compressed]" << std::endl;
        return -1;
    }
    int is_compressed = -1;
    if (argc == 2)
    {
        std::string flag_str = argv[1];
        boost::algorithm::to_lower(flag_str);
        if (flag_str == "1" || flag_str == "true" || flag_str == "yes" ||
            flag_str == "--compressed" || flag_str == "-c")
            is_compressed = 1;
        else if (flag_str == "0" || flag_str == "false" || flag_str == "no" ||
            flag_str == "--uncompressed" || flag_str == "-u")
            is_compressed = 0;
        else
        {
            std::cerr << "IS_COMPRESSED should be true or false." << std::endl;
            return -1;
        }
    }
    std::string arg = read_stdin();
    elliptic_curve_key key;
    if (!read_private_key(key, arg, is_compressed))
    {
        // Try reading it as a public key instead.
        data_chunk pubkey = decode_hex(arg);
        if (pubkey.empty())
        {
            std::cerr << "Invalid private or public key." << std::endl;
            return -1;
        }
        // OK, it's a public key.
        if (!key.set_public_key(pubkey))
        {
            std::cerr << "Invalid public key." << std::endl;
            return -1;
        }
        key.set_compressed(is_compressed >= 0);
    }
    std::cout << key.public_key() << std::endl;
    return 0;
}

