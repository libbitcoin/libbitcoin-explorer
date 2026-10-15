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

#include <unordered_map>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;
using namespace boost::multiprecision;

static constexpr char min_die_char = '1';
static constexpr char max_die_char = '6';
static constexpr auto max_die_value = 6;

// Acceptable configuration settings: dice rolls, entropy bits.
const std::unordered_map<size_t, size_t> configurations
{
    {  50, 128 },
    { 100, 256 }
};

data_chunk dice_to_entropy(const std::string& rolls)
{
    const auto config = configurations.find(rolls.size());
    if (config == configurations.end())
        return {};

    for (auto roll: rolls)
        if (is_limited(roll, min_die_char, max_die_char))
            return {};

    uintx value{};
    for (auto roll: rolls)
        value = value * max_die_value + (roll - min_die_char);

    // Reject incomplete range to avoid modulo bias.
    const auto bits = config->second;
    const auto count = possible_narrow_cast<unsigned>(config->first);
    const uintx die = max_die_value;
    const uintx range = uintx{ one } << bits;
    const uintx limit = (pow(die, count) / range) * range;
    if (value >= limit)
        return {};

    // Big-endian output.
    const uintx number = value % range;
    return to_big_data(data_chunk(bits / byte_bits), number);
}

console_result dice_entropy::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& rolls = get_rolls_argument();

    const auto entropy = dice_to_entropy(rolls);

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
