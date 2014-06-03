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
#include <sx/command/stealth-uncover.hpp>

using namespace libbitcoin;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result stealth_uncover::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 4, 4))
        return console_result::failure;

    const auto ephem_pubkey = decode_hex(argv[1]);
    const auto scan_secret = decode_hash(argv[2]);
    const auto spend_pubkey = decode_hex(argv[3]);
    const auto pubkey = uncover_stealth(ephem_pubkey, scan_secret, spend_pubkey);

    std::cout << pubkey << std::endl;
    return console_result::okay;
}

