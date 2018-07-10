/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/send-tx-node.hpp>

#include <cstddef>
#include <cstdint>
#include <csignal>
#include <future>
#include <iostream>
#include <mutex>
#include <boost/core/null_deleter.hpp>
#include <boost/format.hpp>
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

console_result send_tx_node::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& host = get_host_option();
    const auto& port = get_port_option();
    const tx_type& transaction = get_transaction_argument();

    // Configuration settings.
    //-------------------------------------------------------------------------

    const auto identifier = get_network_identifier_setting();
    const uint8_t retries = get_network_connect_retries_setting();
    const auto connect = get_network_connect_timeout_seconds_setting();
    const auto handshake = get_network_channel_handshake_seconds_setting();
    const auto& hosts_file_name = get_network_hosts_file_setting();
    ////const auto& debug_file_name = get_network_debug_file_setting();
    ////const auto& error_file_name = get_network_error_file_setting();

    network::settings settings(bc::config::settings::mainnet);

    // Manual connection only.
    settings.threads = 1;
    settings.outbound_connections = 0;

    // Guard against retry->attempt overflow.
    const auto overflow = (retries == max_uint8);
    const auto attempts = (overflow ? max_uint8 : retries + 1);

    // Defaulted by bx.
    settings.manual_attempt_limit = attempts;
    settings.connect_timeout_seconds = connect;
    settings.channel_handshake_seconds = handshake;
    ////settings.debug_file = debug_file_name;
    ////settings.error_file = error_file_name;
    settings.hosts_file = hosts_file_name;
    settings.verbose = true;

    // Testnet deviations.
    if (identifier != 0)
        settings.identifier = identifier;

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

    bc::settings bitcoin_settings;
    populate_bitcoin_settings(bitcoin_settings, *this);
    p2p network(settings, bitcoin_settings);
    callback_state state(error, output);
    message::transaction tx(transaction);

    // Catch C signals for aborting the program.
    signal(SIGTERM, handle_stop);
    signal(SIGINT, handle_stop);

    const auto send_handler = [&state](const code& ec)
    {
        if (state.succeeded(ec))
            state.output(BX_SEND_TX_NODE_OUTPUT);

        stop(ec);
    };

    const auto connect_handler = [&state, &tx, send_handler](const code& ec,
        network::channel::ptr node)
    {
        if (state.succeeded(ec))
            node->send(tx, send_handler);
        else
            stop(ec);
    };

    const auto start_handler = [&state](const code& ec)
    {
        if (!state.succeeded(ec))
            stop(ec);
    };

    // We must start the service so that stop can be honored.
    network.start(start_handler);

    // Connect to the one specified host with retry up to the specified limit.
    // This maintains the connection but only invokes handler on first connect.
    network.connect(host, port, connect_handler);

    // Wait until stopped and capture if console stop code.
    state.succeeded(complete.get_future().get());

    // Ensure successful shutdown before return.
    network.close();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
