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
#include <bitcoin/explorer/commands/slip39-decode.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result slip39_decode::invoke(std::ostream& output, std::ostream&)
{
    // Bound parameters.
    const slip39& share = get_share_argument();

    const json::object metadata
    {
        { "identifier", share.identifier() },
        { "extendable", share.extendable() },
        { "exponent", share.exponent() },
        { "group_index", share.group_index() },
        { "group_threshold", share.group_threshold() },
        { "group_count", share.group_count() },
        { "member_index", share.member_index() },
        { "member_threshold", share.member_threshold() }
    };

    write_stream(output, metadata);
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
