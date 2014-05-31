/*
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
#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include <sx/command/addr.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/curve.hpp>

using namespace bc;

bool sx::extensions::addr::invoke(const int argc, const char* argv[])
{
    elliptic_curve_key key;
    if (!read_public_or_private_key(key))
        return false;

    payment_address address;
    set_public_key(address, key.public_key());

    if (argc == 2)
        address.set(atoi(argv[1]), address.hash());

    std::cout << address.encoded() << std::endl;
    return true;
}