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
#include <sx/command/stealth-shared-secret.hpp>

#include <iostream>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/ec_private.hpp>

using namespace libwallet;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::serializer;

console_result stealth_shared_secret::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& secret = get_secret_argument();
    const auto& pubkey = get_pubkey_argument();

    // Pass either (ephem_secret, scan_pubkey) or (scan_secret, ephem_pubkey).
    auto shared = shared_secret(secret, pubkey);

    output << ec_private(shared) << std::endl;
    return console_result::okay;
}

