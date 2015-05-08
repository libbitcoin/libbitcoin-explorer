/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

static void handle_signal(int signal)
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

    bc::ofstream debug_log(debug_file.string(), log_open_mode);
    bc::ofstream error_log(error_file.string(), log_open_mode);
    bind_debug_log(debug_log);
    bind_error_log(error_log);

    async_client client(4);
    auto& pool = client.get_threadpool();
    bc::network::hosts host(pool);
    bc::network::handshake shake(pool);
    bc::network::network net(pool);
    bc::network::protocol proto(pool, host, shake, net);

    callback_state state(error, output);

    const auto start_handler = [&state](const std::error_code& code)
    {
        state.handle_error(code);
    };

    // Forward lambda declarations to enable the cycle between them.
    std::function<void(const std::error_code&)> send_handler;
    std::function<void(const std::error_code&, bc::network::channel_ptr,
        bc::network::protocol&, const tx_type&)> channel_handler;
    
    send_handler = [&state, &proto, &transaction, &channel_handler](
        const std::error_code& code)
    {
        if (state.handle_error(code))
            state.output(format(BX_SEND_TX_P2P_OUTPUT) % now());

        --state;
        if (!state.stopped())
            proto.subscribe_channel(
                std::bind(channel_handler, ph::_1, ph::_2, std::ref(proto),
                    std::ref(transaction)));
    };

    channel_handler = [&state, &send_handler](const std::error_code& code,
        bc::network::channel_ptr node, bc::network::protocol&, 
        const tx_type& tx)
    {
        if (state.handle_error(code))
            node->send(tx, send_handler);
    };

    bool coalesced = false;
    const auto stop_handler = [&state, &coalesced](const std::error_code& code)
    {
        state.handle_error(code);
        coalesced = true;
    };

    // Increment state to the required number of node connections.
    while (state < nodes)
        ++state;

    // Zero nodes specified.
    if (state.stopped())
        return console_result::okay;

    proto.set_max_outbound(nodes * 6);
    proto.start(start_handler);
    proto.subscribe_channel(
        std::bind(channel_handler, ph::_1, ph::_2, std::ref(proto),
            std::ref(transaction)));

    // Catch C signals for stopping the program.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    client.poll(state.stopped(), 2000);
    proto.stop(stop_handler);

    // Delay until the stop handler has been called.
    while (!coalesced)
        sleep_ms(1);

    client.stop();

    return state.get_result();
}
