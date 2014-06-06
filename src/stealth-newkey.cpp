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
#include <wallet/wallet.hpp>
#include <sx/command/stealth-newkey.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/curve.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result stealth_newkey::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1))
        return console_result::failure;

    const auto scan_secret = generate_random_secret();
    const auto spend_secret = generate_random_secret();
    const auto spend_pubkey = secret_to_public_key(spend_secret);

    stealth_address addr;
    addr.options = 0;
    addr.scan_pubkey = secret_to_public_key(scan_secret);
    addr.spend_pubkeys.push_back(spend_pubkey);
    addr.number_signatures = 1;

    std::cout << "Stealth address: " << addr.encoded() << std::endl;
    std::cout << "Scan secret: " << scan_secret << std::endl;
    std::cout << "Spend secret: " << spend_secret << std::endl;
    return console_result::okay;
}

