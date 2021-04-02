/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/mnemonic-new.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;

// Minimum entropy required to create a 12 word seed.
constexpr size_t minimum_safe_entropy_size = 16;

console_result mnemonic_new::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const dictionary& language = get_language_option();
    const data_chunk& entropy = get_entropy_argument();

    if (entropy.size() < minimum_safe_entropy_size)
    {
        error << BX_MNEMONIC_NEW_UNSAFE_ENTROPY << std::endl;
        return console_result::failure;
    }

    if ((entropy.size() % mnemonic_seed_multiple) != 0u)
    {
        error << BX_MNEMONIC_NEW_INVALID_ENTROPY << std::endl;
        return console_result::failure;
    }

    // Language parser defaults to 'en'.
    const auto words = wallet::create_mnemonic(entropy, language);

    output << join(words) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
