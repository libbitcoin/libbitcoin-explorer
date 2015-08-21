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

#include <bitcoin/explorer/commands/mnemonic-new.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>

using namespace bc;
using namespace bc::wallet;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result mnemonic_new::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const dictionary_list& language = get_language_option();
    const data_chunk& entropy = get_seed_argument();

    const auto entropy_size = entropy.size();

    if ((entropy_size % bc::wallet::mnemonic_seed_multiple) != 0)
    {
        error << BX_EC_MNEMONIC_NEW_INVALID_ENTROPY << std::endl;
        return console_result::failure;
    }

    // If 'any' is indicated, default to 'en', otherwise use as specified.
    auto dictionary = &bc::wallet::language::en;
    if (language.size() == 1)
        dictionary = language.front();

    const auto words = create_mnemonic(entropy, *dictionary);

    output << join(words) << std::endl;
    return console_result::okay;
}
