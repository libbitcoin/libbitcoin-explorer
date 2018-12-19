/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/send-tx-p2p.hpp>

#include <cstddef>
#include <cstdint>
#include <csignal>
#include <future>
#include <iostream>
#include <mutex>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/core/null_deleter.hpp>
#include <bitcoin/network.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace boost;
using namespace bc::explorer::config;
using namespace bc::network;
using namespace bc::system;

static const uint32_t hosts_pool_capacity = 1000;
static std::promise<code> complete;

// Manage the race between console stop and network stop.
static void stop(const code& ec)
{
    static std::once_flag stop_mutex;
    std::call_once(stop_mutex, [&](){ complete.set_value(ec); });
}

// Handle the console stop signal.
static void handle_stop(int)
{
    stop(error::service_stopped);
}

console_result send_tx_p2p::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto nodes = get_nodes_option();
    const tx_type& transaction = get_transaction_argument();

    // Configuration settings.
    //-------------------------------------------------------------------------

    const auto identifier = get_network_identifier_setting();
    const auto connect = get_network_connect_timeout_seconds_setting();
    const auto handshake = get_network_channel_handshake_seconds_setting();
    const auto& hosts_file_name = get_network_hosts_file_setting();
    ////const auto& debug_file_name = get_network_debug_file_setting();
    ////const auto& error_file_name = get_network_error_file_setting();
    const auto& seeds = get_network_seeds_setting();

    // Defaults to 8 outbound connections.
    network::settings settings(system::config::settings::mainnet);

    // Defaulted by bx.
    settings.connect_timeout_seconds = connect;
    settings.channel_handshake_seconds = handshake;
    settings.host_pool_capacity = hosts_pool_capacity;
    ////settings.debug_file = debug_file_name;
    ////settings.error_file = error_file_name;
    settings.hosts_file = hosts_file_name;
    settings.verbose = true;

    // Testnet deviations.
    if (identifier != 0)
        settings.identifier = identifier;

    if (!seeds.empty())
        settings.seeds = seeds;

    // Log initialization.
    //-------------------------------------------------------------------------

    ////const log::rotable_file debug_file
    ////{
    ////    settings.debug_file,
    ////    settings.archive_directory,
    ////    settings.rotation_size,
    ////    settings.maximum_archive_size,
    ////    settings.minimum_free_space,
    ////    settings.maximum_archive_files
    ////};

    ////const log::rotable_file error_file
    ////{
    ////    settings.error_file,
    ////    settings.archive_directory,
    ////    settings.rotation_size,
    ////    settings.maximum_archive_size,
    ////    settings.minimum_free_space,
    ////    settings.maximum_archive_files
    ////};

    ////log::stream console_out(&output, null_deleter());
    ////log::stream console_err(&error, null_deleter());
    ////log::initialize(debug_file, error_file, console_out, console_err);

    ////static const auto header = format("=========== %1% ==========") % symbol();
    ////LOG_DEBUG(LOG_NETWORK) << header;
    ////LOG_ERROR(LOG_NETWORK) << header;

    // Network operations.
    //-------------------------------------------------------------------------

    p2p network(settings);
    callback_state state(error, output);
    message::transaction tx(transaction);

    // Increment state to the required number of node connections.
    while (state < nodes)
        ++state;

    // Zero nodes specified.
    if (state.stopped())
        return console_result::okay;

    // Catch C signals for aborting the program.
    signal(SIGTERM, handle_stop);
    signal(SIGINT, handle_stop);

    const auto send_handler = [&state](const code& ec)
    {
        // If error keep trying.
        if (ec)
            return;

        // Handle each successful send.
        state.output(BX_SEND_TX_P2P_OUTPUT);
        --state;

        // If done visiting nodes set complete.
        if (state.stopped())
            stop(ec);
    };

    const auto connect_handler = [&state, &tx, send_handler](const code& ec,
        channel::ptr node)
    {
        // If error keep trying.
        if (ec)
            return true;

        // Send and resubscribe to connections.
        node->send(tx, send_handler);
        return true;
    };

    const auto run_handler = [&state, &network](const code& ec)
    {
        if (!state.succeeded(ec))
            stop(ec);
    };

    const auto start_handler = [&state, &network, connect_handler,
        run_handler](const code& ec)
    {
        if (!state.succeeded(ec))
        {
            stop(ec);
            return;
        }

        network.subscribe_connection(connect_handler);
        network.run(run_handler);
    };

    // Connect to the specified number of hosts from the host pool.
    // This attempts to maintain the set of connections, so it will always
    // eventually achieve the target, and sometimes go over due to the race.
    network.start(start_handler);

    // Wait until stopped and capture if console stop code.
    state.succeeded(complete.get_future().get());

    // Ensure successful shutdown before return.
    network.close();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
