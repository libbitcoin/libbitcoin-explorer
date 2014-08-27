/*
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#include <explorer/commands/stealth-new.hpp>

#include <iostream>
#include <wallet/wallet.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/ec_public.hpp>

using namespace libwallet;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

console_result stealth_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& scan_pubkey = get_scan_pubkey_argument();
    const auto& spend_pubkey = get_spend_pubkey_argument();
    const auto& ephemeral_secret = get_ephemeral_secret_argument();

    auto ephemeral_pubkey = initiate_stealth(ephemeral_secret, scan_pubkey,
        spend_pubkey);

    output << ec_public(ephemeral_pubkey) << std::endl;
    return console_result::okay;
}

