/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/electrum-new.hpp>

#include <cmath>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;

// Requires a seed of at least 17 bytes (136 bits).
static const size_t minimum_electrum_words = 12;

console_result electrum_new::invoke(std::ostream& output, std::ostream& error)
{
#ifdef WITH_ICU
    // Bound parameters.
    const dictionary_list& language = get_language_option();
    const data_chunk& seed = get_seed_argument();
    const auto prefix = get_prefix_option();

    // trunc(log2(2048)) = 11
    const auto word_bits = static_cast<size_t>(std::log2(dictionary_size));

    // 17 * 8 = 136
    const auto seed_bits = seed.size() * byte_bits;

    // 136 / 11 = 12
    const auto words = seed_bits / word_bits;

    if (words < minimum_electrum_words)
    {
        error << BX_ELECTRUM_NEW_INVALID_SEED << std::endl;
        return console_result::failure;
    }

    // If 'any' default to first ('en'), otherwise the one specified.
    const auto dictionary = language.front();

    auto mnemonic = electrum::create_mnemonic(seed, *dictionary, prefix);

    output << join(mnemonic) << std::endl;
    return console_result::okay;
#else
    error << BX_ELECTRUM_REQUIRES_ICU << std::endl;
    return console_result::failure;
#endif
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
