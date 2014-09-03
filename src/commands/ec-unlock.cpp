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
#include <explorer/commands/ec-unlock.hpp>

#include <iostream>
#include <explorer/define.hpp>

using namespace explorer;
using namespace explorer::commands;

console_result ec_unlock::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    //const auto& passphrase = get_passphrase_argument();
    
    // TODO: implement BIP38

    error << BX_EC_UNLOCK_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}