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
#include <sx/command/stealth-uncover-public.hpp>

#include <iostream>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/ec_public.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result stealth_uncover_public::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& scan_secret = get_scan_secret_argument();
    const auto& spend_pubkey = get_spend_pubkey_argument();
    const auto& ephemeral_pubkey = get_ephemeral_pubkey_argument();

    auto scan_pubkey = uncover_stealth(ephemeral_pubkey, scan_secret,
        spend_pubkey);

    output << ec_public(scan_pubkey) << std::endl;
    return console_result::okay;
}