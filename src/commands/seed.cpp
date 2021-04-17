/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/commands/seed.hpp>

#include <cstddef>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

console_result seed::invoke(std::ostream& output, std::ostream& error)
{
    const auto bit_length = get_bit_length_option();

    // These are soft requirements for security and rationality.
    // Use bit vs. byte length input as the more familiar convention.
    if ((bit_length < (minimum_seed_size * byte_bits)) ||
        (bit_length % byte_bits) != 0)
    {
        error << BX_SEED_BIT_LENGTH_UNSUPPORTED << std::endl;
        return console_result::failure;
    }

    const auto new_seed = [](size_t bit_length)
    {
        const auto fill_seed_size = bit_length / byte_bits;
        data_chunk seed(fill_seed_size);
        pseudo_random_fill(seed);
        return seed;
    };

    // Use of prng limits testability.
    const auto seed = new_seed(bit_length);

    output << base16(seed) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
