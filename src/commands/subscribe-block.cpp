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

#include <bitcoin/explorer/commands/subscribe-block.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/client.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result subscribe_block::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto duration = get_duration_option();
    client server(*this, get_server_url_argument());

    const auto notify = [&output](const json::value& hash) NOEXCEPT
    {
        write_stream(output, hash);
        return true;
    };

    if (!server.subscribe(error, "block/subscribe", duration, notify))
        return console_result::failure;

    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
