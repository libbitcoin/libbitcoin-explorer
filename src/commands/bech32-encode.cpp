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
#include <bitcoin/explorer/commands/bech32-encode.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

constexpr uint8_t version_maximum = 16;

console_result bech32_encode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const uint8_t version = get_version_option();
    const auto& prefix = get_prefix_argument();
    const data_chunk& program = get_program_argument();

    if (witness_address::parse_prefix(prefix) !=
        witness_address::parse_result::valid)
    {
        error << BX_BECH32_ENCODE_INVALID_PREFIX << std::endl;
        return console_result::failure;
    }

    if (version > version_maximum)
    {
        error << BX_BECH32_ENCODE_INVALID_VERSION << std::endl;
        return console_result::failure;
    }

    if (program.size() < witness_address::program_minimum_size)
    {
        error << BX_BECH32_ENCODE_SHORT_PROGRAM << std::endl;
        return console_result::failure;
    }

    if (program.size() > witness_address::program_maximum_size)
    {
        error << BX_BECH32_ENCODE_LONG_PROGRAM << std::endl;
        return console_result::failure;
    }

    const witness_address address(program, version, prefix);
    if (!address)
    {
        error << BX_BECH32_ENCODE_INVALID_PROGRAM << std::endl;
        return console_result::failure;
    }

    output << address << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
