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

#include <csignal>
#include <iostream>
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

static void handle_signal(int signal)
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
    const auto& node = get_host_option();
    const auto& port = get_port_option();
    const tx_type& transaction = get_transaction_argument();
    const auto& debug_file = get_logging_debug_file_setting();
    const auto& error_file = get_logging_error_file_setting();

    // These haven't been used for node (or p2p) connections.
    const auto retries = get_general_retries_setting();
    const auto wait = get_general_wait_setting();

    bc::ofstream debug_log(debug_file.string(), log_open_mode);
    bc::ofstream error_log(error_file.string(), log_open_mode);
    bind_debug_log(debug_log);
    bind_error_log(error_log);

    const static auto headline = "================= Startup =================";
    log_fatal(LOG_NETWORK) << headline;
    log_error(LOG_NETWORK) << headline;
    log_warning(LOG_NETWORK) << headline;
    log_info(LOG_NETWORK) << headline;
    log_debug(LOG_NETWORK) << headline;

    constexpr size_t threads = 4;
    constexpr size_t poll_period_ms = 2000;

    async_client client(threads);
    auto& pool = client.get_threadpool();
    bc::network::hosts host(pool, 0);
    bc::network::handshake shake(pool);
    bc::network::network net(pool);
    bc::network::protocol proto(pool, host, shake, net);

    callback_state state(error, output);

    const auto start_handler = [&state](const std::error_code& code)
    {
        state.handle_error(code);
    };

    const auto send_handler = [&state](const std::error_code& code)
    {
        if (state.handle_error(code))
            state.output(format(BX_SEND_TX_NODE_OUTPUT) % now());

        --state;
    };

    const auto channel_handler = [&state, &send_handler](
        const std::error_code& code, bc::network::channel_ptr node,
        bc::network::protocol&, const tx_type& tx)
    {
        if (state.handle_error(code))
            node->send(tx, send_handler);
    };

    bool stopped = false;
    const auto stop_handler = [&state, &stopped](const std::error_code& code)
    {
        state.handle_error(code);
        stopped = true;
    };

    ++state;

    // Handle each successful connection.
    proto.subscribe_channel(
        std::bind(channel_handler,
            ph::_1, ph::_2, std::ref(proto), std::ref(transaction)));

    // Connect to the explicitly-specified host.
    proto.maintain_connection(node, port, false);

    // Catch C signals for aborting the program.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    client.poll(state.stopped(), poll_period_ms);
    proto.stop(stop_handler);
    client.stop();

    return state.get_result();
}
