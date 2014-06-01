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
#include <sx/command/hd_priv.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;

// TODO: extract commad-specific error message and centralize implementation.
bool read_hd_priv_args(const int argc, const char* argv[],
    bool& is_hard, uint32_t& index)
{
    index = 0;
    is_hard = false;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--hard")
            is_hard = true;
        else if (!sx::to_number(arg, index))
        {
            std::cerr << "hd-priv: Bad INDEX provided." << std::endl;
            return false;
        }
    }

    return true;
}

bool sx::extensions::hd_priv::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 3))
        return false;

    bool is_hard;
    uint32_t index;
    if (!read_hd_priv_args(argc, argv, is_hard, index))
        return false;

    hd_private_key private_key;
    std::string encoded_key = read_stdin();
    if (!private_key.set_serialized(encoded_key))
    {
        std::cerr << "hd-priv: error reading private key." << std::endl;
        return false;
    }

    if (is_hard)
        index += first_hardened_key;

    auto child_key = private_key.generate_private_key(index);
    if (!child_key.valid())
    {
        std::cerr << "hd-priv: error deriving child key." << std::endl;
        return false;
    }

    std::cout << child_key.serialize() << std::endl;
    return true;
}

