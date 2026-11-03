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

#include <bitcoin/explorer/commands/mnemonic-encode.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result mnemonic_encode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const system::language lingo = get_language_option();
    const data_chunk& entropy = get_entropy_argument();

    if (!mnemonic::is_valid_entropy_size(entropy.size()))
    {
        error << BX_MNEMONIC_ENCODE_INVALID_ENTROPY_SIZE << std::endl;
        return console_result::failure;
    }

    // An unspecified language defaults to English.
    const auto identifier = lingo == language::none ? language::en : lingo;
    const mnemonic instance(entropy, identifier);
    if (!instance)
    {
        error << BX_MNEMONIC_ENCODE_INVALID_ENTROPY_SIZE << std::endl;
        return console_result::failure;
    }

    output << instance.sentence() << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
