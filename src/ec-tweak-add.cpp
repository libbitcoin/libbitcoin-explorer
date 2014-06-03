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
#include <bitcoin/bitcoin.hpp>
#include <sx/command/ec-tweak-add.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/curve.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result ec_tweak_add::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 3, 3))
        return console_result::failure;

    ec_secret int_part;
    ec_point point_part;
    if (!ec_math_parse_args(argc, argv, int_part, point_part))
    {
        std::cerr << "sx: Unable to read input values." << std::endl;
        return console_result::failure;
    }

    bool success = bc::ec_tweak_add(point_part, int_part);
    if (!success)
    {
        line_out(std::cerr, "sx: Out of range.");
        return console_result::failure;
    }

    std::cout << point_part << std::endl;
    return console_result::okay;
}

