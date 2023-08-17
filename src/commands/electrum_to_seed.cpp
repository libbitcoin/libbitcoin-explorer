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
#include <bitcoin/explorer/commands/electrum-to-seed.hpp>

#include <functional>
#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc;
using namespace bc::config;
using namespace bc::wallet;

// Limit seed creation to 12 words of entropy.
constexpr size_t minimum_safe_words = 12;

console_result electrum_to_seed::invoke(std::ostream& output,
    std::ostream& error)
{
#ifndef WITH_ICU
    error << BX_ELECTRUM_TO_SEED_REQUIRES_ICU << std::endl;
    return console_result::failure;
#else

    // Bound parameters.
    const auto& dictionaries = get_languages_option();
    const auto& passphrase = get_passphrase_option();
    const auto prefix = get_version_option();
    const auto& words = get_words_argument();

    if (words.size() < minimum_safe_words)
    {
        error << BX_ELECTRUM_TO_SEED_UNSAFE_SENTENCE << std::endl;
        return console_result::failure;
    }

    // Any word set works regardless of language validation.
    if (!dictionaries.empty() &&
        !electrum::validate_mnemonic(words, to_lexicon(dictionaries), prefix))
    {
        error << BX_ELECTRUM_TO_SEED_INVALID_LANGUAGES << std::endl;
        return console_result::failure;
    }

    // Validation (above) and decoding requires ICU normalization.
    const auto seed = electrum::decode_mnemonic(words, passphrase);

    output << base16(seed) << std::endl;
    return console_result::okay;
#endif
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
