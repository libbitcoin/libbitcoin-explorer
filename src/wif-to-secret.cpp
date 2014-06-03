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
#include <sx/command/wif-to-secret.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result wif_to_secret::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 1))
        return console_result::failure;

    const auto wif = read_stream(std::cin);
    const auto secret = libwallet::wif_to_secret(wif);
    if (secret == null_hash)
    {
        std::cerr << "Invalid private key." << std::endl;
        return console_result::failure;
    }

    std::cout << secret << std::endl;
    return console_result::okay;
}

