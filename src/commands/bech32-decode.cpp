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
#include <bitcoin/explorer/commands/bech32-decode.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::json;
using namespace bc::system::wallet;

console_result bech32_decode::invoke(std::ostream& output,
    std::ostream& error)
{
    std::string prefix{};
    uint8_t version{};
    data_chunk program{};
    const auto result = witness_address::parse_address(prefix, version,
        program, trim_copy(get_address_argument()));

    if (result == witness_address::parse_result::checksum_invalid)
    {
        error << BX_BECH32_DECODE_INVALID_CHECKSUM << std::endl;
        return console_result::failure;
    }

    if (result != witness_address::parse_result::valid)
    {
        error << BX_BECH32_DECODE_INVALID << std::endl;
        return console_result::failure;
    }

    write_stream(output, object
    {
        { "bech32", object
            {
                { "prefix", prefix },
                { "program", encode_base16(program) },
                { "version", version }
            }
        }
    });

    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
