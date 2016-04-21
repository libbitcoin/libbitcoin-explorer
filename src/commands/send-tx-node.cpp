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

#include <bitcoin/explorer/commands/send-tx-node.hpp>

#include <cstddef>
#include <cstdint>
#include <csignal>
#include <future>
#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/network.hpp>
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

console_result send_tx_node::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& host = get_host_option();
    const auto& port = get_port_option();
    const tx_type& transaction = get_transaction_argument();

    const auto identifier = get_network_identifier_setting();
    const uint8_t retries = get_network_connect_retries_setting();
    const auto connect = get_network_connect_timeout_seconds_setting();
    const auto handshake = get_network_channel_handshake_seconds_setting();
    const auto& hosts_file = get_network_hosts_file_setting();
    const auto& debug_file = get_network_debug_file_setting();
    const auto& error_file = get_network_error_file_setting();

    // TODO: give option to send errors to console vs. file.
    bc::ofstream debug_log(debug_file.string(), log_open_mode);
    bc::ofstream error_log(error_file.string(), log_open_mode);
    initialize_logging(debug_log, error_log, output, error);

    static const auto header = format("=========== %1% ==========") % symbol();
    log::debug(LOG_NETWORK) << header;
    log::error(LOG_NETWORK) << header;

    network::settings settings(bc::settings::mainnet);

    // Fixed non-defaults: not relay/port/inbound/seeds/hosts/outbound.
    settings.host_pool_capacity = 0;
    settings.outbound_connections = 0;
    settings.inbound_port = 0;
    settings.inbound_connections = 0;
    settings.relay_transactions = false;
    settings.seeds.clear();

    // Guard against retry->attempt overflow.
    const auto overflow = retries <= (max_uint8 - 1u);
    const auto attempts = overflow ? max_uint8 : retries;

    // Defaulted by bx.
    settings.manual_attempt_limit = attempts;
    settings.connect_timeout_seconds = connect;
    settings.channel_handshake_seconds = handshake;
    settings.hosts_file = hosts_file;

    // Testnet deviations.
    if (identifier != 0)
        settings.identifier = identifier;

    p2p network(settings);
    std::promise<code> complete;
    callback_state state(error, output);

    const auto send_handler = [&state, &complete](const code& ec)
    {
        if (state.succeeded(ec))
            state.output(format(BX_SEND_TX_NODE_OUTPUT) % now());

        complete.set_value(ec);
    };

    const auto connect_handler = [&state, &transaction, &send_handler](
        const code& ec, network::channel::ptr node)
    {
        if (state.succeeded(ec))
            node->send(transaction, send_handler);
    };

    // Connect to the one specified host with retry up to the specified limit.
    network.connect(host, port, connect_handler);

    // Catch C signals for aborting the program.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);
    
    // Wait until callback indicates completion (connect or timeout).
    complete.get_future();

    return state.get_result();
}
