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
#include <sx/command/seed.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/base16.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result seed::invoke(std::ostream& output, std::ostream& error)
{
    const auto bit_length = get_bit_length_option();

    // This are soft requirements for security and rationality.
    // We use bit vs. byte length input as the more familiar convention.
    if (bit_length * byte_size < minimum_seed_size ||
        bit_length % byte_size != 0)
    {
        error << SX_SEED_BIT_LENGTH_UNSUPPORTED << std::endl;
        return console_result::failure;
    }

    const auto seed = new_seed(bit_length);

    output << base16(seed) << std::endl;
    return console_result::okay;
}