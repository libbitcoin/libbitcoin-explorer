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

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

// Face values 1 to 16, so a roll of 1 contributes zero.
static constexpr std::string_view faces{ "123456789abcdefg" };
static constexpr uint8_t minimum_sides = 2;
static constexpr uint8_t maximum_sides = 16;

// The number of rolls required for at least the given bits of entropy.
static size_t rolls_for(size_t bits, uint8_t sides) NOEXCEPT
{
    const uint512_t range = uint512_t{ one } << bits;
    size_t count{};

    for (uint512_t power{ one }; power < range; power *= sides)
        ++count;

    return count;
}

static data_chunk dice_to_entropy(const std::string& rolls,
    uint8_t sides) NOEXCEPT
{
    const auto count = rolls.size();
    size_t bits{};

    if (count == rolls_for(128, sides))
        bits = 128;
    else if (count == rolls_for(256, sides))
        bits = 256;
    else
        return {};

    const auto digits = faces.substr(0, sides);
    uint512_t value{};

    for (const auto roll: rolls)
    {
        const auto digit = digits.find(roll);
        if (digit == std::string_view::npos)
            return {};

        value = value * sides + digit;
    }

    // Reject the incomplete range to avoid modulo bias.
    const uint512_t range = uint512_t{ one } << bits;
    const auto limit = (power<uint512_t>(sides, count) / range) * range;
    if (value >= limit)
        return {};

    // Big-endian output.
    const uint512_t number = value % range;
    return to_big_data(data_chunk(bits / byte_bits), number);
}

console_result dice_entropy::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto sides = get_sides_option();
    const auto& rolls = get_rolls_argument();

    if (is_limited(sides, minimum_sides, maximum_sides))
    {
        error << BX_DICE_SIDES_INVALID << std::endl;
        return console_result::failure;
    }

    const auto entropy = dice_to_entropy(rolls, sides);
    if (entropy.empty())
    {
        error << BX_DICE_ROLLS_INVALID << std::endl;
        return console_result::failure;
    }

    output << base16(entropy) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
