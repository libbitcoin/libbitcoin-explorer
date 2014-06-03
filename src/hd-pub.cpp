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
#include <wallet/wallet.hpp>
#include <sx/command/hd-pub.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;

static bool private_to_public_key()
{
    hd_private_key private_key;
    if (!private_key.set_serialized(sx::read_stream(std::cin)))
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
        // Special case - read private key from STDIN and convert it to public.
        return private_to_public_key();
    }

    bool is_hard;
    uint32_t index;
    if (!read_hard_index_args(argc, argv, is_hard, index))
    {
        std::cerr << "sx: Bad INDEX provided." << std::endl;
        return false;
    }

    // TODO: constrain read_hard_index_args so that the encoded key can be 
    // provided as an argument, and then update documentation.
    std::string encoded_key(read_stream(std::cin));
    
    hd_public_key public_key;
    hd_private_key private_key;

    // NOTE: same idiom in hd_to_address
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

