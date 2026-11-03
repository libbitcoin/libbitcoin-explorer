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
#include <bitcoin/explorer/commands/dice-entropy.hpp>

#include <string>
#include <string_view>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

// Face values 0 to 15, written as hexadecimal digits.
static constexpr std::string_view faces{ "0123456789abcdef" };
static constexpr size_t maximum_bits = 1024;

using number = uintx_t<maximum_bits>;

// The value of the rolls and the size of their range.
static bool to_number(number& value, number& total, const std::string& rolls,
    uint8_t sides) NOEXCEPT
{
    if (rolls.size() * bit_width(sub1(sides)) >= maximum_bits)
        return false;

    const auto digits = faces.substr(zero, sides);
    value = zero;
    total = one;

    for (const auto roll: rolls)
    {
        const auto digit = digits.find(roll);
        if (digit == std::string_view::npos)
            return false;

        value = value * sides + digit;
        total *= sides;
    }

    return true;
}

console_result dice_entropy::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto sides = get_sides_option();
    const auto& rolls = get_rolls_argument();

    if (is_limited(sides, minimum_dice_sides, maximum_dice_sides))
    {
        error << BX_DICE_ENTROPY_SIDES_INVALID << std::endl;
        return console_result::failure;
    }

    number value{};
    number total{};
    if (!to_number(value, total, rolls, sides))
    {
        error << BX_DICE_ENTROPY_INVALID << std::endl;
        return console_result::failure;
    }

    // The entropy is the whole bytes of the range of the rolls.
    const auto size = to_floored_bytes(floored_log2(total));
    if (is_zero(size) ||
        rolls.size() != roll_count(sides, size))
    {
        error << BX_DICE_ENTROPY_COUNT << std::endl;
        return console_result::failure;
    }

    // Reject the incomplete top multiple of the range to avoid modulo bias.
    const auto range = power2<number>(to_bits(size));
    if (value >= floored_divide(total, range) * range)
    {
        error << BX_DICE_ENTROPY_REJECTED << std::endl;
        return console_result::failure;
    }

    // Big-endian output.
    const auto entropy = floored_modulo(value, range);
    output << base16(to_big_data(data_chunk(size), entropy)) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
