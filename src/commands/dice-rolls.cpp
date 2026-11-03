/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/dice-rolls.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result dice_rolls::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto sides = get_sides_option();
    const size_t bits = get_bits_option();

    if (is_limited(sides, minimum_dice_sides, maximum_dice_sides))
    {
        error << BX_DICE_ROLLS_SIDES_INVALID << std::endl;
        return console_result::failure;
    }

    const auto bytes = to_floored_bytes(bits);
    if (to_bits(bytes) != bits ||
        is_limited(bytes, one, maximum_dice_bytes))
    {
        error << BX_DICE_ROLLS_BITS_INVALID << std::endl;
        return console_result::failure;
    }

    output << roll_count(sides, bytes) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
