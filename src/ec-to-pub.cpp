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
#include <sx/command/ec-to-pub.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result ec_to_pub::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    const auto secret = get_secret_argument();
    const auto uncompressed = get_uncompressed_option();

    const auto public_key = secret_to_public_key(secret, !uncompressed);

    output << ec_public(public_key) << std::endl;
    return console_result::okay;
}