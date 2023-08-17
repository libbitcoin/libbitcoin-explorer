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
#include <bitcoin/explorer/commands/mnemonic-to-seed.hpp>

#include <functional>
#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::config;
using namespace bc::wallet;

// Limit seed creation to 12 words of entropy.
constexpr size_t minimum_safe_words = 12;

console_result mnemonic_to_seed::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& languages = get_languages_option();
    const auto& passphrase = get_passphrase_option();
    const auto& words = get_words_argument();

#ifndef WITH_ICU
    if (!passphrase.empty())
    {
        error << BX_MNEMONIC_TO_SEED_PASSPHRASE_REQUIRES_ICU << std::endl;
        return console_result::failure;
    }
#endif

    if (words.size() < minimum_safe_words)
    {
        error << BX_MNEMONIC_TO_SEED_UNSAFE_SENTENCE << std::endl;
        return console_result::failure;
    }

    if ((words.size() % mnemonic_word_multiple) != 0u)
    {
        error << BX_MNEMONIC_TO_SEED_INVALID_SENTENCE << std::endl;
        return console_result::failure;
    }

    // Any word set divisible by 3 works regardless of language validation.
    if (!languages.empty() &&
        !validate_mnemonic(words, to_lexicon(languages)))
    {
        error << BX_MNEMONIC_TO_SEED_INVALID_LANGUAGES << std::endl;
        return console_result::failure;
    }

#ifdef WITH_ICU
    // Passphrase requires ICU normalization.
    const auto seed = wallet::decode_mnemonic(words, passphrase);
#else
    const auto seed = wallet::decode_mnemonic(words);
#endif

    output << base16(seed) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
