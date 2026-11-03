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
#include <bitcoin/explorer/utility.hpp>

using namespace bc::system;

namespace libbitcoin {
namespace explorer {

std::ostream& write_stream(std::ostream& output,
    const system::json::value& value)
{
    output << system::json::serialize(value) << std::endl;
    return output;
}

size_t roll_count(uint8_t sides, size_t bytes) NOEXCEPT
{
    using number = uintx_t<1024>;

    if (is_limited(sides, minimum_dice_sides, maximum_dice_sides) ||
        is_limited(bytes, one, maximum_dice_bytes))
        return zero;

    const auto range = power2<number>(to_bits(bytes));
    const auto limit = power2<number>(to_bits(add1(bytes)));
    number total{ one };
    size_t rolls{};

    while (total < range)
    {
        total *= sides;
        ++rolls;
    }

    // Maximize the accepted fraction of the rolls, k * range / total, where k
    // is the number of whole ranges in the total.
    size_t count{};
    number best{};
    number best_total{ one };

    for (; total < limit; total *= sides, ++rolls)
    {
        const auto whole = floored_divide(total, range);
        if (whole * best_total > best * total)
        {
            count = rolls;
            best = whole;
            best_total = total;
        }
    }

    return count;
}

} // namespace explorer
} // namespace libbitcoin
