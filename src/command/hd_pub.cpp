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
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;

bool invoke(const int argc, const char* argv[])
{
    // Special case - read private key from STDIN and
    // convert it to a public key.
    if (argc == 1)
    {
        std::string encoded_key = read_stdin();
        hd_private_key private_key;
        if (!private_key.set_serialized(encoded_key))
        {
            std::cerr << "sx: Error reading private key." << std::endl;
            return -1;
        }
        const hd_public_key public_key = private_key;
        std::cout << public_key.serialize() << std::endl;
        return 0;
    }
    bool is_hard = false;
    uint32_t index = 0;
    if (!read_hd_command_args(argc, argv, is_hard, index))
        return -1;
    // Arguments now parsed. Read key from STDIN.
    std::string encoded_key = read_stdin();
    hd_public_key key;

    // First try loading private key.
    hd_private_key private_key;
    if (private_key.set_serialized(encoded_key))
        key = private_key;
    else if (!key.set_serialized(encoded_key))
    {
        std::cerr << "sx: Error reading key." << std::endl;
        return -1;
    }

    if (!private_key.valid() && is_hard)
    {
        std::cerr << "sx: Cannot use --hard with public keys."
            << std::endl;
        return -1;
    }

    hd_public_key out;
    // You must use the private key to generate --hard keys.
    if (is_hard)
    {
        index += libwallet::first_hardened_key;
        out = private_key.generate_public_key(index);
    }
    else
        out = key.generate_public_key(index);

    if (!out.valid())
    {
        std::cerr << "sx: Error deriving child key." << std::endl;
        return -1;
    }
    std::cout << out.serialize() << std::endl;
    return 0;
}

