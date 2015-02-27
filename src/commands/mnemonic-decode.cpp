/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitcoin/explorer/commands/mnemonic-decode.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result mnemonic_decode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& passphrase = get_passphrase_option();
    const auto& words = get_words_argument();

    auto word_count = words.size();
    if (word_count < 12) {
        error << BX_EC_MNEMONIC_DECODE_SHORT_SENTENCE << std::endl;
        return console_result::failure;
    }
    if ((word_count % 3) != 0) {
        error << BX_EC_MNEMONIC_DECODE_LENGTH_INVALID_SENTENCE << std::endl;
        return console_result::failure;
    }
    if (word_count > max_word_count) {
        error << BX_EC_MNEMONIC_DECODE_SENTENCE_LENGTH_EXCEEDED << std::endl;
        return console_result::failure;
    }

    const auto seed = decode_mnemonic(words, passphrase);
    if (seed.size() == 0) {
        error << BX_EC_MNEMONIC_DECODE_SENTENCE_INVALID << std::endl;
        return console_result::failure;
    }

    std::string sentence = std::string(encode_base16(seed));
    output << sentence << std::endl;
    return console_result::okay;
}

