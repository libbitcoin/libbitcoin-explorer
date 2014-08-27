/**
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
#include <explorer/commands/hd-to-wif.hpp>

#include <wallet/wallet.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/wif.hpp>

using namespace libwallet;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

// 100% coverage by line, loc ready.
console_result hd_to_wif::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const hd_private_key& secret = get_hd_private_key_argument();

    // TESTNET OPTION DOES NOT REQUIRE RECOMPILE

    output << wif(secret) << std::endl;
    return console_result::okay;
}