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

#include <bitcoin/explorer/commands/version.hpp>

#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/version.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::client;
using namespace bc::explorer::config;
using namespace bc::system;

console_result version::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto connection = get_connection(*this);

    obelisk_client client(connection.retries);
    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output);

    auto on_done = [&state](const code& error, const std::string& version)
    {
        if (!state.succeeded(error))
        {
            state.output(format(BX_VERSION_FAILED) % error.message());
            return;
        }

        static const std::string explorer_version{ LIBBITCOIN_EXPLORER_VERSION };

        state.output(format(BX_SERVER_VERSION) % version);
        state.output(format(BX_EXPLORER_VERSION) % explorer_version);
    };

    client.server_version(on_done);
    client.wait();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
