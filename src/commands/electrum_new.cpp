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
#include <bitcoin/explorer/commands/electrum-new.hpp>

#include <cmath>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc;
using namespace bc::wallet;

// Minimum entropy required to create a 12 word seed.
constexpr size_t twelve_word_minimum_entropy_size = 17;

console_result electrum_new::invoke(std::ostream& output, std::ostream& error)
{
#ifndef WITH_ICU
    error << BX_ELECTRUM_NEW_REQUIRES_ICU << std::endl;
    return console_result::failure;
#else
    // Bound parameters.
    const dictionary& language = get_language_option();
    const auto prefix = get_version_option();
    const data_chunk& entropy = get_entropy_argument();

    if (entropy.size() < twelve_word_minimum_entropy_size)
    {
        error << BX_ELECTRUM_NEW_UNSAFE_ENTROPY << std::endl;
        return console_result::failure;
    }

    // Language parser defaults to 'en'.
    // Creation requires ICU normalization.
    const auto mnemonic = electrum::create_mnemonic(entropy, language, prefix);

    output << join(mnemonic) << std::endl;
    return console_result::okay;
#endif
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
