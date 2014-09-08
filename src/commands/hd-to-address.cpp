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
#include <explorer/commands/hd-to-address.hpp>

#include <explorer/define.hpp>
#include <explorer/primitives/address.hpp>

using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

// 100% coverage by line, loc ready.
console_result hd_to_address::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& key = get_hd_key_argument();

    // Get public from private and otherwise get public.
    const auto public_key = key.derived_public_key();

    // RECOMPILE OF REQUIRED FOR TESTNET.

    output << address(public_key) << std::endl;
    return console_result::okay;
}