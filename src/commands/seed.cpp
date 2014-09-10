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
#include <explorer/commands/seed.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/base16.hpp>
#include <explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result seed::invoke(std::ostream& output, std::ostream& error)
{
    const auto bit_length = get_bit_length_option();

    // This are soft requirements for security and rationality.
    // We use bit vs. byte length input as the more familiar convention.
    if (bit_length < minimum_seed_size * byte_bits ||
        bit_length % byte_bits != 0)
    {
        error << BX_SEED_BIT_LENGTH_UNSUPPORTED << std::endl;
        return console_result::failure;
    }

    const auto seed = new_seed(bit_length);

    output << base16(seed) << std::endl;
    return console_result::okay;
}