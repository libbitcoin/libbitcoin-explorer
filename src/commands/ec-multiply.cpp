/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
#include <explorer/commands/ec-multiply.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/ec_public.hpp>

using namespace bc;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

// 100% coverage by line, loc ready.
console_result ec_multiply::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& point = get_point_argument();
    const auto& secret = get_secret_argument();

    // Elliptic curve product (POINT * INTEGER).
    ec_public product(point);
    if (!bc::ec_multiply(product.data(), secret))
    {
        error << BX_EC_MULITPLY_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    output << product << std::endl;
    return console_result::okay;
}

