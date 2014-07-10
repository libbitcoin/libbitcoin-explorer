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
#include <sx/command/addr.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/key.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result addr::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    auto key = get_key_argument();
    auto version = get_version_option();

    // TODO: generate a flag to indicate whether optional values are set.
    bool versioned = true;

    // Get the public key's payment address.
    auto ripemd160 = bitcoin_short_hash(key);

    // WARNING: pubkey_version varies by libbitcoin *compilation*.
    // TODO: make libbitcoin testnet dynamic and then do the same here.
    // auto testnet = get_general_testnet_setting();
    version = if_else(versioned, version, payment_address::pubkey_version);

    auto pay_address = payment_address(version, ripemd160);

    output << address(pay_address) << std::endl;
    return console_result::okay;
}