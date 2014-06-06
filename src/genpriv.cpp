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
#include <sx/command/genpriv.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result genpriv::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 2, 3))
        return console_result::failure;

    size_t key_number;
    if (!parse(key_number, argv[1]))
    {
        std::cerr << "genpriv: Bad N provided." << std::endl;
        return console_result::failure;
    }

    bool for_change = (argc == 3 && is_true(argv[2]));
    deterministic_wallet wallet;
    if (!wallet.set_seed(read_stream(std::cin)))
    {
        std::cerr << "genpriv: This command wants a seed." << std::endl;
        return console_result::failure;
    }

    bool is_compressed = false;
    secret_parameter secret = wallet.generate_secret(key_number, for_change);
    std::cout << secret_to_wif(secret, is_compressed) << std::endl;
    return console_result::okay;
}