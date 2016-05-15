/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitcoin/explorer/commands/watch-address.hpp>

#include <csignal>
#include <cstddef>
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;
using namespace bc::wallet;

static void handle_signal(int signal)
{
    // Can't pass args using lambda capture for a simple function pointer.
    // This means there's no way to terminate without using a global variable.
    exit(console_result::failure);
}

// This command only halts on failure or timeout.
// BUGBUG: the server may drop the connection, which is not presently detected.
console_result watch_address::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& address = get_payment_address_argument();
    const auto connection = get_connection(*this);

    // TODO: add monitoring timeout to command line in seconds, default to 600.
    const auto timeout = uint32_t(10 * 60); //// get_timeout_option();

    obelisk_client client(connection);

    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    auto on_subscribed = [&state, &address]()
    {
        state.output(format(BX_WATCH_ADDRESS_WAITING) % address);
        ++state;
    };

    auto on_error = [&state](const code& error)
    {
        state.succeeded(error);
    };

    // The configured timeout is used for the subscription.
    client.address_subscribe(on_error, on_subscribed, address);
    client.wait();

    // If subscription succeeded, handle updates until monitoring timeout.
    if (state.stopped())
        return state.get_result();

    // This enables json-style array formatting.
    const auto json = encoding == encoding_engine::json;

    auto on_update = [&output, &state, json](const payment_address& address,
        size_t, const hash_digest& block_hash, const tx_type& tx)
    {
        state.output(prop_tree(tx, block_hash, address, json));
        output << std::endl;
    };

    client.set_on_update(on_update);

    // Catch C signals for stopping the program before monitoring timeout.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    // Handle updates until monitoring timeout.
    client.monitor(timeout);

    return state.get_result();
}
