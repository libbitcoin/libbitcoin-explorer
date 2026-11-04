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
#include <bitcoin/explorer/commands/electrum-v1-to-seed.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result electrum_v1_to_seed::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const system::language lingo = get_language_option();
    const auto& words = get_words_argument();

    if (!electrum_v1::is_valid_word_count(words.size()))
    {
        error << BX_ELECTRUM_V1_TO_SEED_INVALID_WORD_COUNT << std::endl;
        return console_result::failure;
    }

    const electrum_v1 instance(words, lingo);
    if (!instance)
    {
        error << BX_ELECTRUM_V1_TO_SEED_INVALID_WORDS << std::endl;
        return console_result::failure;
    }

    output << encode_base16(instance.to_seed().secret()) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
