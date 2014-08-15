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
#include <sx/command/stealth-address-decode.hpp>

#include <iostream>
#include <sx/define.hpp>
#include <sx/utility/utility.hpp>

using namespace sx;
using namespace sx::extension;

console_result stealth_address_decode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& address = get_stealth_argument();

    write_stream(output, address, encoding) << std::endl;
    return console_result::okay;
}

