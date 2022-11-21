/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;
using namespace bc::system::wallet;

////<define name="BX_ELECTRUM_TO_SEED_INVALID_WORD_COUNT" value="The word count is not 12 to 46." />
////<define name="BX_ELECTRUM_TO_SEED_INVALID_WORDS" value="The mnemonic is not from the specified dictionary. Non-dictionary mnemonics are not supported." />
////<define name="BX_ELECTRUM_TO_SEED_INVALID_WORDS_ICU" value="The mnemonic is not from the specified dictionary. This is not an ICU build, so ensure that the mnemonic is prenormalized. Non-dictionary mnemonics are not supported." />
////<define name="BX_ELECTRUM_TO_SEED_PASSPHRASE_ICU" value="This is not an ICU build, so the passphrase is limited to ascii characters." />

console_result electrum_to_seed::invoke(std::ostream& output,
    std::ostream& error)
{
////#ifdef WITH_ICU
////    // Bound parameters.
////    const auto& passphrase = get_passphrase_option();
////    const auto& words = get_words_argument();
////
////    // Decoding requires ICU normalization.
////    if (passphrase.empty())
////        output << base16(electrum::decode_mnemonic(words)) << std::endl;
////    else
////        output << base16(electrum::decode_mnemonic(words, passphrase))
////            << std::endl;
////
////    return console_result::okay;
////#else
////    error << BX_ELECTRUM_REQUIRES_ICU << std::endl;
////    return console_result::failure;
////#endif

    return console_result::failure;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
