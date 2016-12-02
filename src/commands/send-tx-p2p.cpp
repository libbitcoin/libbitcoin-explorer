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
#include <bitcoin/network.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/transaction.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::explorer::config;
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

//    // TODO: give option to send errors to console vs. file.
//    bc::ofstream debug_log(debug_file.string(), log::append);
//    bc::ofstream error_log(error_file.string(), log::append);
//    initialize_logging(debug_log, error_log, output, error);

    static const auto header = format("=========== %1% ==========") % symbol();
    LOG_DEBUG(LOG_NETWORK) << header;
    LOG_ERROR(LOG_NETWORK) << header;

    // Defaults to 8 outbound connections.
    network::settings settings(bc::config::settings::mainnet);

    // Defaulted by bx.
    settings.connect_timeout_seconds = connect;
    settings.channel_handshake_seconds = handshake;
    settings.hosts_file = hosts_file;

    // Testnet deviations.
    if (identifier != 0)
        settings.identifier = identifier;

    if (!seeds.empty())
        settings.seeds = seeds;

    p2p network(settings);
    std::promise<code> started;
    std::promise<code> complete;
    callback_state state(error, output);
    p2p::connect_handler connect_handler;

    const auto start_handler = [&started](const code& ec)
    {
        started.set_value(ec);
    };

    const auto handle_send = [&state, &complete, &network, &connect_handler](
        const code& ec)
    {
        if (state.succeeded(ec))
            state.output(BX_SEND_TX_P2P_OUTPUT);

        --state;

        // If done visiting nodes set complete.
        if (state.stopped())
            complete.set_value(ec);
    };

    message::transaction tx_msg(transaction);

    connect_handler = [&state, &tx_msg, handle_send](
        const code& ec, channel::ptr node)
    {
        if (state.succeeded(ec))
            node->send(tx_msg, handle_send);

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
    network.subscribe_connection(connect_handler);

    // Connect to the specified number of hosts from the host pool.
    // This attempts to maintain the set of connections, so it will always
    // eventually achieve the target, and sometimes go over due to the race.
    network.start(start_handler);

    if (started.get_future().get())
        return console_result::failure;

    // Catch C signals for aborting the program.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    // Wait until callback indicates completion.
    complete.get_future();

    // Ensure successful shutdown.
    // This call saves the hosts file and blocks until thread coalescence.
    network.close();

    return state.get_result();
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
