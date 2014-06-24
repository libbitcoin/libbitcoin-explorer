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
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/command/addr.hpp>
#include <sx/utility/coin.hpp>
//#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result addr::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    auto key = get_key_argument();
    auto version = get_version_option();

    // Convert the input to a key.
    elliptic_curve_key ec_key;
    if (!read_public_or_private_key(ec_key, key))
    {
        cerr << boost::format(SX_ADDR_INVALID_KEY) % key << std::endl;
        return console_result::failure;
    }

    // Get the (public key) payment address from the public or private key.
    payment_address address;
    set_public_key(address, ec_key.public_key());

    // Set the desired key version, using zero as a sentinel for 'not set'.
    // TODO: generate a flag to indicate wheher optional values are set.
    if (version > 0)
        address.set(version, address.hash());

    output << address.encoded() << std::endl;
    return console_result::okay;
}