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

#include <bitcoin/explorer/commands/watch-address.hpp>

#include <csignal>
#include <cstddef>
#include <iostream>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/config/transaction.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::client;
using namespace bc::explorer::config;
using namespace bc::wallet;

static void handle_signal(int signal)
{
    // TODO: exit without process termination.
    exit(console_result::failure);
}

// This command only halts on failure or timeout.
// BUGBUG: the server may drop the connection, which is not presently detected.
console_result watch_address::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& address = get_payment_address_argument();
    const auto connection = get_connection(*this);
    const auto duration = get_duration_option();

    obelisk_client client(connection);

    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output);

    auto on_subscribed = [&state, &address](const code& error)
    {
        if (state.succeeded(error))
        {
            state.output(format(BX_WATCH_ADDRESS_WAITING) % address);
            ++state;
        }
    };

    auto on_error = [&state](const code& error)
    {
        state.succeeded(error);
    };

    auto on_update = [&output, &state, &address](const code& error,
        uint16_t sequence, size_t height, const hash_digest& tx_hash)
    {
        if (state.succeeded(error))
        {
            output
                << sequence << " " << height << " " << encode_hash(tx_hash)
                << std::endl;
        }
    };

    client.set_on_update(on_update);
    client.subscribe_address(on_error, on_subscribed, address);
    client.wait();

    if (state.stopped())
        return state.get_result();

    // Catch C signals for stopping the program before monitoring timeout.
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    // Handle updates until monitoring duration expires.
    // TODO: revise client to allow for stop notification from another thread.
    client.monitor(duration);

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
