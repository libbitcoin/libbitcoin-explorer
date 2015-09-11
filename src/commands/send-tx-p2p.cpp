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

#include <bitcoin/explorer/commands/send-tx-p2p.hpp>

#include <cstddef>
#include <cstdint>
#include <csignal>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/async_client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

static void handle_signal(int)
{
    // Can't pass args using lambda capture for a simple function pointer.
    // This means there's no way to terminate without using a global variable
    // or process termination. Since the variable would screw with testing all 
    // other methods we opt for process termination here.
    exit(console_result::failure);
}

// BUGBUG: mainnet/testnet determined by libbitcoin compilation.
console_result send_tx_p2p::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto nodes = get_nodes_option();
    const tx_type& transaction = get_transaction_argument();
    const auto& debug_file = get_logging_debug_file_setting();
    const auto& error_file = get_logging_error_file_setting();
    const auto& hosts_file = get_general_hosts_file_setting();
    const auto connect = get_general_connect_timeout_seconds_setting();
    const auto handshake = get_general_channel_handshake_seconds_setting();

    // TODO: give option to send errors to console vs. file.
    static const auto header = format("=========== %1% ==========") % symbol();
    bc::ofstream debug_log(debug_file.string(), log_open_mode);
    bind_debug_log(debug_log);
    log_debug(LOG_NETWORK) << header;
    bc::ofstream error_log(error_file.string(), log_open_mode);
    bind_error_log(error_log);
    log_error(LOG_NETWORK) << header;

    // Not listening, no relay.
    static constexpr bool relay = false;
    static constexpr size_t threads = 4;
    static constexpr uint16_t listen = 0;
    const network::timeout timeouts(connect, handshake);

    async_client client(threads);
    network::hosts hosts(client.pool(), hosts_file);
    network::initiator net(client.pool(), timeouts);
    network::protocol proto(client.pool(), hosts, net, listen, relay);

    callback_state state(error, output);
    network::protocol::channel_handler handle_connect;

    const auto protocol_handler = [&state](const std::error_code& code)
    {
        state.succeeded(code);
    };

    const auto handle_send = [&state, &proto, &transaction, &handle_connect](
        const std::error_code& code)
    {
        if (state.succeeded(code))
            state.output(format(BX_SEND_TX_P2P_OUTPUT) % now());

        // Success or failed, if not done visiting nodes resubscribe.
        --state;
        if (!state.stopped())
            proto.subscribe_channel(handle_connect);
    };

    handle_connect = [&state, &transaction, handle_send](
        const std::error_code& code, network::channel::ptr node)
    {
        if (state.succeeded(code))
            node->send(transaction, handle_send);
    };

    // Increment state to the required number of node connections.
    while (state < nodes)
        ++state;

    // Zero nodes specified.
    if (state.stopped())
        return console_result::okay;

    // Handle each successful connection.
    proto.subscribe_channel(handle_connect);

    // Connect to the specified number of hosts from the host pool.
    proto.start(protocol_handler);

    // Catch C signals for aborting the program.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    client.poll(state.stopped());
    proto.stop(protocol_handler);
    client.stop();

    return state.get_result();
}
