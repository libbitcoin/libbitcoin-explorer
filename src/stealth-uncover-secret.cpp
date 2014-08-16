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
#include "precompile.hpp"
#include <sx/command/stealth-uncover-secret.hpp>

#include <iostream>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/ec_private.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result stealth_uncover_secret::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& scan_secret = get_scan_ec_private_key_argument();
    const auto& spend_secret = get_spend_ec_private_key_argument();
    const auto& ephemeral_pubkey = get_ephemeral_ec_public_key_argument();

    auto private_key = uncover_stealth_secret(ephemeral_pubkey, scan_secret,
        spend_secret);

    output << ec_private(private_key) << std::endl;
    return console_result::okay;
}

