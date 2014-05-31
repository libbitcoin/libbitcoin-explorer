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
    bool is_hard = false;
    uint32_t index = 0;
    if (!read_hd_command_args(argc, argv, is_hard, index))
        return -1;
    // Arguments now parsed. Read key from STDIN.
    std::string encoded_key = read_stdin();
    hd_private_key key;
    if (!key.set_serialized(encoded_key))
    {
        std::cerr << "hd-priv: error reading private key." << std::endl;
        return -1;
    }
    if (is_hard)
        index += libwallet::first_hardened_key;

    auto out = key.generate_private_key(index);
    if (!out.valid())
    {
        std::cerr << "hd-priv: error deriving child key." << std::endl;
        return -1;
    }
    std::cout << out.serialize() << std::endl;
    return 0;
}

