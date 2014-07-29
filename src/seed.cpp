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
#include <sx/command/seed.hpp>

#include <iostream>
#include <sx/serializer/bytes.hpp>
#include <sx/utility/utility.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result seed::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Arbitrary 128 bit length for generated seeds.
    constexpr size_t fill_seed_size = 128 / sizeof(uint8_t);

    // TODO: allow for seed length specification in multiples of 32 bits.

    data_chunk seed(fill_seed_size);
    random_fill(seed);

    output << bytes(seed) << std::endl;
    return console_result::okay;
}