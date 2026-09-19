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

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using boost::multiprecision::cpp_int;

static constexpr auto bits_per_byte = 8;

// Acceptable configuration settings: dice rolls, entropy bits
const std::unordered_map<uint16_t, uint16_t> configurations =
{
    {  50, 128 },
    { 100, 256 }
};

data_chunk dice_to_entropy(const std::string& rolls)
{
    const auto config = configurations.find(rolls.size());
    if (config == configurations.end())
        return {};

    cpp_int n = 0;

    for (char c : rolls) {
        if (c < '1' || c > '6')
            return {};

        n = n * 6 + (c - '1');
    }

    const auto bits = config->second;
    const cpp_int range = cpp_int(1) << bits;

    cpp_int input_space = 1;
    for (int i = 0; i < config->first; ++i)
        input_space *= 6;

    const cpp_int limit = (input_space / range) * range;

    // Reject the incomplete range to avoid modulo bias.
    if (n >= limit)
        return {};

    n %= range;

    data_chunk result(config->second / bits_per_byte);

    // Big-endian output.
    for (int i = (config->second / bits_per_byte) - 1; i >= 0; --i) {
        result[i] = static_cast<unsigned char>(n & 0xff);
        n >>= bits_per_byte;
    }

    return result;
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
