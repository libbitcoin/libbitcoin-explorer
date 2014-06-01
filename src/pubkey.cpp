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
#include <sx/command/pubkey.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

int get_compression(const int argc, const char* argv[])
{
    using namespace sx;

    if (argc > 1)
    {
        std::string arg(argv[1]);
        bool compressed = is_true(arg) || is_flag(arg, "compressed");
        bool uncompressed = is_false(arg) || is_flag(arg, "uncompressed");
        if (!compressed && !uncompressed)
        {
            std::cerr << "COMPRESSION is specified incorrectly." << std::endl;
            return false;
        }

        return (compressed || !uncompressed ? 1 : 0);
    }

    return -1;
}

bool sx::extensions::pubkey::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return false;

    // TODO: swap integer flags for three state enum.
    int is_compressed = get_compression(argc, argv);

    std::string input(read_stdin());
    elliptic_curve_key key;
    if (!read_private_key(key, input, is_compressed))
    {
        // Try reading it as a public key instead.
        data_chunk pubkey = decode_hex(input);
        if (pubkey.empty())
        {
            std::cerr << "Invalid private or public key." << std::endl;
            return false;
        }
        // OK, it's a public key.
        if (!key.set_public_key(pubkey))
        {
            std::cerr << "Invalid public key." << std::endl;
            return false;
        }
        key.set_compressed(is_compressed == 1);
    }

    std::cout << key.public_key() << std::endl;
    return true;
}

