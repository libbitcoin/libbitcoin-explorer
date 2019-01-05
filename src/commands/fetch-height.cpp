/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/fetch-height.hpp>

#include <cstddef>
#include <iostream>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::client;
using namespace bc::explorer::config;
using namespace bc::system;

console_result fetch_height::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& server_url = get_server_url_argument();
    const auto& public_key = get_public_key_argument();
    auto connection = get_connection(*this);

    // For this command only, allow command line to override server config.
    if (!server_url.empty())
    {
        connection.server = server_url;

        if (!connection.server)
        {
            display_connection_failure(error, connection.server);
            return console_result::failure;
        }

        if (!public_key.empty())
        {
            connection.server_public_key = public_key;

            if (!connection.server_public_key)
            {
                display_connection_failure(error, connection.server);
                return console_result::failure;
            }
        }
    }

    obelisk_client client(connection.retries);
    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output);

    auto on_done = [&state](const code& ec, size_t height)
    {
        if (!state.succeeded(ec))
            return;

        state.output(height);
    };

    client.blockchain_fetch_last_height(on_done);
    client.wait();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
