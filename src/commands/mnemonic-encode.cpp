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

#include <bitcoin/explorer/commands/mnemonic-encode.hpp>

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

static libbitcoin::bip39_language get_bip39_language(
    primitives::bip39_language language)
{
    std::map<const std::string, libbitcoin::bip39_language> languages = {
        { "en", libbitcoin::bip39_language::en },
        { "ja", libbitcoin::bip39_language::ja },
        { "es", libbitcoin::bip39_language::es },
        { "zh", libbitcoin::bip39_language::zh_Hans },
    };
    std::string lang = std::string(language);
    if (languages.find(lang) == languages.end()) {
        return libbitcoin::bip39_language::en;
    }
    return languages[lang];
}

console_result mnemonic_encode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& language = get_language_argument();
    const data_chunk& seed = get_seed_argument();

    if (seed.size() < minimum_seed_size) {
        error << BX_EC_MNEMONIC_ENCODE_SHORT_SEED << std::endl;
        return console_result::failure;
    }
    if ((seed.size() % 4) != 0) {
        error << BX_EC_MNEMONIC_ENCODE_SHORT_SEED << std::endl;
        return console_result::failure;
    }

    const auto sentence = join(
        encode_mnemonic(seed, get_bip39_language(language)));

    output << sentence << std::endl;
    return console_result::okay;
}
