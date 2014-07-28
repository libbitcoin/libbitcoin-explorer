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
#include <sx/command/base58-decode.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result base58_decode::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto encoded = get_base58_argument();

    output << bytes(encoded) << std::endl;
    return console_result::okay;
}