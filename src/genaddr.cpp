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
#include <sx/command/genaddr.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result genaddr::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 2, 3))
        return console_result::failure;

    size_t key_number;
    if (!parse<size_t>(argv[1], key_number))
    {
        std::cerr << "genaddr: Bad N provided." << std::endl;
        return console_result::failure;
    }

    bool for_change = (argc == 3 && is_true(argv[2]));

    deterministic_wallet wallet;
    std::string seed = read_stream(std::cin);
    if (!wallet.set_seed(seed))
    {
        data_chunk mpk = decode_hex(seed);
        if (!wallet.set_master_public_key(mpk))
        {
            std::cerr << "genaddr: No valid master public key, or "
                << "private secret key was passed in." << std::endl;
            return console_result::failure;
        }
    }

    payment_address addr;
    data_chunk pubkey = wallet.generate_public_key(key_number, for_change);
    set_public_key(addr, pubkey);
    std::cout << addr.encoded() << std::endl;
    return console_result::okay;
}