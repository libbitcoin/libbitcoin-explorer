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

// Sponsored in part by Digital Contract Design, LLC

#include <bitcoin/explorer/commands/fetch-compact-filter-checkpoint-node.hpp>

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
using namespace std::placeholders;

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

console_result fetch_compact_filter_checkpoint_node::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& host = get_host_option();
    const auto& port = get_port_option();
    const auto& encoding = get_format_option();
    const hash_digest& hash = get_hash_argument();
    const uint8_t type = get_type_argument();

    // Configuration settings.
    //-------------------------------------------------------------------------

    const auto identifier = get_network_identifier_setting();
    const uint8_t retries = get_network_connect_retries_setting();
    const auto connect = get_network_connect_timeout_seconds_setting();
    const auto handshake = get_network_channel_handshake_seconds_setting();
    const auto& hosts_file_name = get_network_hosts_file_setting();

    network::settings settings(system::config::settings::mainnet);

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
    settings.hosts_file = hosts_file_name;
    settings.verbose = true;

    // Testnet deviations.
    if (identifier != 0)
        settings.identifier = identifier;

    // Network operations.
    //-------------------------------------------------------------------------

    p2p network(settings);
    callback_state state(error, output);
    message::get_compact_filter_checkpoint request(type, hash);

    // Catch C signals for aborting the program.
    signal(SIGTERM, handle_stop);
    signal(SIGINT, handle_stop);

    // This enables json-style array formatting.
    const auto json = encoding == encoding_engine::json;

    auto receive_handler = [&state, json](const code& ec,
        std::shared_ptr<const message::compact_filter_checkpoint> response)
    {
        if (state.succeeded(ec) && response)
            state.output(property_tree(*response, json));

        stop(ec);

        return false;
    };

    const auto send_handler = [&state](const code& ec)
    {
        if (!state.succeeded(ec))
            stop(ec);
    };

    const auto connect_handler = [&state, &receive_handler, &request, send_handler](
        const code& ec, network::channel::ptr node)
    {
        if (state.succeeded(ec))
        {
            bool supports_bip157 = (node->peer_version()->services() &
                message::version::service::node_compact_filters) != 0;

            if (supports_bip157)
            {
                node->template subscribe<message::compact_filter_checkpoint>(
                    std::move(receive_handler));

                node->send(request, send_handler);
            }
            else
            {
                state.error(BX_BIP157_UNSUPPORTED);
                stop(error::posix_to_error_code(console_result::failure));
            }
        }
        else
            stop(ec);
    };

    const auto start_handler = [&output, &state](const code& ec)
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
