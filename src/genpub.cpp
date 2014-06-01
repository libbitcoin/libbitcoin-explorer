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
#include <sx/command/genpub.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;

bool sx::extensions::genpub::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 2, 4))
        return false;

    size_t key_number;
    if (!parse<size_t>(argv[1], key_number))
    {
        std::cerr << "genaddr: Bad N provided" << std::endl;
        return false;
    }

    bool for_change = (argc > 2 && is_true(argv[2]));

    size_t stop_limit = key_number;
    if (argc > 3 && !parse<size_t>(argv[3], stop_limit))
    {
        std::cerr << "genaddr: Bad RANGESTOP provided" << std::endl;
        return false;
    }

    if (stop_limit < key_number)
    {
        std::cerr << "genaddr: RANGESTOP cannot be less than N" << std::endl;
        return false;
    }

    deterministic_wallet wallet;
    std::string seed = read_stdin();
    if (!wallet.set_seed(seed))
    {
        data_chunk mpk = decode_hex(seed);
        if (!wallet.set_master_public_key(mpk))
        {
            std::cerr << "genaddr: No valid master public key, or "
                << "private secret key was passed in." << std::endl;
            return false;
        }
    }

    for (size_t i = key_number; i <= stop_limit; ++i)
    {
        data_chunk public_key = wallet.generate_public_key(i, for_change);
        std::cout << public_key << std::endl;
    }

    return false;
}


