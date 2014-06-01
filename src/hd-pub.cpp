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
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/command/hd-pub.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;

// TODO: extract commad-specific error message and centralize implementation.
bool read_hd_pub_args(const int argc, const char* argv[],
    bool& is_hard, uint32_t& index)
{
    index = 0;
    is_hard = false;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--hard")
            is_hard = true;
        else if (!sx::parse<size_t>(arg, index))
        {
            std::cerr << "hd-pub: Bad INDEX provided." << std::endl;
            return false;
        }
    }

    return true;
}

// Special case - read private key from STDIN and convert it to a public key.
bool private_to_public_key()
{
    hd_private_key private_key;
    if (!private_key.set_serialized(sx::read_stdin()))
    {
        std::cerr << "sx: Error reading private key." << std::endl;
        return false;
    }

    const hd_public_key public_key = private_key;
    std::cout << public_key.serialize() << std::endl;
    return true;
}

bool sx::extensions::hd_pub::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 3))
        return false;

    if (argc == 1)
    {
        return private_to_public_key();
    }

    bool is_hard;
    uint32_t index;
    if (!read_hd_pub_args(argc, argv, is_hard, index))
        return false;
    
    hd_public_key public_key;
    hd_private_key private_key;
    std::string encoded_key = read_stdin();

    // First try loading private key and otherwise the public key.
    if (private_key.set_serialized(encoded_key))
        public_key = private_key;
    else if (!public_key.set_serialized(encoded_key))
    {
        std::cerr << "sx: Error reading key." << std::endl;
        return false;
    }

    if (!private_key.valid() && is_hard)
    {
        std::cerr << "sx: Cannot use --hard with public keys."
            << std::endl;
        return false;
    }

    hd_public_key child_key;
    if (is_hard)
    {
        // You must use the private key to generate --hard keys.
        index += first_hardened_key;
        child_key = private_key.generate_public_key(index);
    }
    else
        child_key = public_key.generate_public_key(index);

    if (!child_key.valid())
    {
        std::cerr << "sx: Error deriving child key." << std::endl;
        return false;
    }

    std::cout << child_key.serialize() << std::endl;
    return true;
}

