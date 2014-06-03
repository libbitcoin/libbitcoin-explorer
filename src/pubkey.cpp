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
#include <sstream>
#include <sx/command/pubkey.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/dispatch.hpp>

using namespace bc;

static bool get_compression(const int argc, const char* argv[],
    sx::key_compression& is_compressed)
{
    is_compressed = sx::key_compression::unspecified;

    if (argc > 1)
    {
        std::string arg(argv[1]);

        // NOTE: boolean argument has been removed from this parser in favor of
        // consistency with the use of flags in all other commands.
        bool compressed = sx::is_option(arg, SX_OPTION_COMPRESSED);
        bool uncompressed = sx::is_option(arg, SX_OPTION_UNCOMPRESSED);

        // NOTE: it's not currently possible for two to be specified but it is
        // possible for one to be bogus and another unspecified (invalid).
        if (compressed == uncompressed)
            return false;

        is_compressed = (compressed || !uncompressed ? 
            sx::key_compression::on : sx::key_compression::off);
    }

    return true;
}

bool sx::extensions::pubkey::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return false;

    key_compression is_compressed;
    if (!get_compression(argc, argv, is_compressed))
    {
        std::cerr << "Inconsistent compression options." << std::endl;
        return false;
    }

    // TODO: allow for reading from args.
    std::string input(read_stream(std::cin));

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
        key.set_compressed(is_compressed == key_compression::on);
    }

    std::cout << key.public_key() << std::endl;
    return true;
}

