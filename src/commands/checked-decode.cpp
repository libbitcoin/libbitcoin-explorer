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
#include <bitcoin/explorer/commands/checked-decode.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/json.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result checked_decode::invoke(std::ostream& output,
    std::ostream& error)
{
    const data_chunk& checked = get_checked_argument();

    if (checked.size() <= checksum_default_size || !verify_checksum(checked))
    {
        error << BX_CHECKED_DECODE_INVALID_CHECKSUM << std::endl;
        return console_result::failure;
    }

    write_stream(output, checked_to_json(checked));
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
