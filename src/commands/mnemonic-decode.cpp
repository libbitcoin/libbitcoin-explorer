/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

// TODO: change implementation from Electrum to BIP39.
console_result mnemonic_decode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& words = get_words_argument();

    if (words.size() < 3)
    {
        error << BX_EC_MNEMONIC_DECODE_SHORT_SENTENCE << std::endl;
        return console_result::failure;
    }

    // Note that there is no dictionary validation in decode_mnemonic.
    const auto hexidecimal = decode_mnemonic(words);

    output << hexidecimal << std::endl;
    return console_result::okay;
}
