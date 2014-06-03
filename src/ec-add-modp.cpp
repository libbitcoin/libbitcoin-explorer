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
#include <sx/command/ec-add-modp.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/curve.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result ec_add_modp::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 3, 3))
        return console_result::failure;

    ec_secret secret_a, secret_b;
    if (!set_ec_secret(secret_a, argv[1]))
    {
        std::cerr << "sx: Invalid secret " << argv[1] << std::endl;
        return console_result::failure;
    }
    if (!set_ec_secret(secret_b, argv[2]))
    {
        std::cerr << "sx: Invalid secret " << argv[2] << std::endl;
        return console_result::failure;
    }
    if (!ec_add(secret_a, secret_b))
    {
        std::cerr << "sx: Error adding numbers." << std::endl;
        return console_result::failure;
    }

    std::cout << secret_a << std::endl;
    return console_result::okay;
}

