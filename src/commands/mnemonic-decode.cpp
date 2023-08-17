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
#include <bitcoin/explorer/commands/mnemonic-decode.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

////<define name="BX_MNEMONIC_DECODE_INVALID_WORD_COUNT" value="The word count is not 12, 15, 18, 21, or 24." />
////<define name="BX_MNEMONIC_DECODE_INVALID_WORDS" value="The mnemonic is not from the specified dictionary." />
////<define name="BX_MNEMONIC_DECODE_INVALID_WORDS_ICU" value="The mnemonic is not from the specified dictionary. This is not an ICU build. Ensure that the mnemonic is prenormalized." />

console_result mnemonic_decode::invoke(std::ostream& output,
    std::ostream& error)
{
    ////// Bound parameters.
    ////const dictionary_list& language = get_language_option();
    ////const data_chunk& entropy = get_seed_argument();

    ////const auto entropy_size = entropy.size();

    ////if ((entropy_size % wallet::mnemonic_seed_multiple) != 0)
    ////{
    ////    error << BX_MNEMONIC_NEW_INVALID_SEED << std::endl;
    ////    return console_result::failure;
    ////}

    ////// If 'any' default to first ('en'), otherwise the one specified.
    ////const auto dictionary = language.front();
    ////const auto words = create_mnemonic(entropy, *dictionary);

    ////output << join(words) << std::endl;
    ////return console_result::okay;

    return console_result::failure;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
