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
#include <sx/serializer/address.hpp>
#include <sx/utility/coin.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result addr::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const auto key = get_key_argument();
    auto version = get_version_option();

    // TODO: generate a flag to indicate whether optional values are set.
    bool versioned = true;

    // TODO: create ec_key (public or private) serializer.
    elliptic_curve_key ec_key;
    if (!read_public_or_private_key(ec_key, key))
    {
        cerr << boost::format(SX_ADDR_INVALID_KEY) % key << std::endl;
        return console_result::failure;
    }

    // Get the public key's payment address.
    auto hash = bitcoin_short_hash(ec_key.public_key());
    version = if_else(versioned, version, payment_address::pubkey_version);
    address address(payment_address(version, hash));

    output << address << std::endl;
    return console_result::okay;
}