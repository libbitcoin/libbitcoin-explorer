/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include "precompile.hpp"
#include <sx/command/mnemonic-decode.hpp>

#include <iostream>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extension;

// $ echo "people blonde admit dart couple different truth common alas
//   stumble time cookie" | sx mnemonic-decode
console_result mnemonic_decode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& words = get_words_argument();

    // TODO: change implementation from Electrum to BIP39.

    // Note that there is no dictionary validation in decode_mnemonic.
    const auto sentence = decode_mnemonic(words);

    output << sentence << std::endl;
    return console_result::okay;
}

