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
#include <future>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;
using namespace bc::network;

static void handle_signal(int)
{
    // Can't pass args using lambda capture for a simple function pointer.
    // This means there's no way to terminate without using a global variable
    // or process termination. Since the variable would screw with testing all 
    // other methods we opt for process termination here.
    exit(console_result::failure);
}

console_result send_tx_p2p::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto nodes = get_nodes_option();
    const tx_type& transaction = get_transaction_argument();

    const auto identifier = get_network_identifier_setting();
    const auto connect = get_network_connect_timeout_seconds_setting();
    const auto handshake = get_network_channel_handshake_seconds_setting();
    const auto& hosts_file = get_network_hosts_file_setting();
    const auto& debug_file = get_network_debug_file_setting();
    const auto& error_file = get_network_error_file_setting();
    const auto& seeds = get_network_seeds_setting();

    // TODO: give option to send errors to console vs. file.
    bc::ofstream debug_log(debug_file.string(), log_open_mode);
    bc::ofstream error_log(error_file.string(), log_open_mode);
    initialize_logging(debug_log, error_log, output, error);

    static const auto header = format("=========== %1% ==========") % symbol();
    log::debug(LOG_NETWORK) << header;
    log::error(LOG_NETWORK) << header;

    auto configuration = p2p::mainnet;

    // Fixed non-defaults: not relay/port/inbound.
    configuration.inbound_port = 0;
    configuration.connection_limit = 0;
    configuration.relay_transactions = false;

    // Defaulted by bx.
    configuration.connect_timeout_seconds = connect;
    configuration.channel_handshake_seconds = handshake;
    configuration.hosts_file = hosts_file;

    // Testnet deviations.
    if (identifier != 0)
        configuration.identifier = identifier;

    if (!seeds.empty())
        configuration.seeds = seeds;

    p2p network(configuration);
    std::promise<code> started;
    std::promise<code> complete;
    std::promise<code> stopped;
    callback_state state(error, output);
    p2p::connect_handler connect_handler;

    const auto start_handler = [&started](const code& ec)
    {
        started.set_value(ec);
    };

    const auto stop_handler = [&stopped](const code& ec)
    {
        stopped.set_value(ec);
    };

    const auto handle_send = [&state, &complete, &network, &connect_handler](
        const code& ec)
    {
        if (state.succeeded(ec))
            state.output(format(BX_SEND_TX_P2P_OUTPUT) % now());

        --state;

        // If done visiting nodes set complete.
        if (state.stopped())
            complete.set_value(ec);
    };

    connect_handler = [&state, &transaction, handle_send](const code& ec,
        channel::ptr node)
    {
        if (state.succeeded(ec))
            node->send(transaction, handle_send);

        // Always resbscribe (stop will clear).
        return true;
    };

    // Increment state to the required number of node connections.
    while (state < nodes)
        ++state;

    // Zero nodes specified.
    if (state.stopped())
        return console_result::okay;

    // Handle each successful connection.
    network.subscribe(connect_handler);

    // Connect to the specified number of hosts from the host pool.
    // This attempts to maintain the set of connections, so it will always
    // eventually achieve the target, and sometimes go over due to the race.
    network.start(start_handler);
    started.get_future();

    // Catch C signals for aborting the program.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    // Wait until callback indicates completion.
    complete.get_future();

    // Ensure successful shutdown.
    // This call saves the hosts file and blocks until thread coalescence.
    network.stop(stop_handler);
    stopped.get_future();

    return state.get_result();
}
