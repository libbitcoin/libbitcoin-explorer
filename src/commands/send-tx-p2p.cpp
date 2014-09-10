/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include "precompile.hpp"
#include <explorer/commands/send-tx-p2p.hpp>

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/callback_state.hpp>
#include <explorer/async_client.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/transaction.hpp>
#include <explorer/utility/utility.hpp>

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

// Started protocol, node discovery complete.
static void handle_start(callback_state& state)
{
    state.output(BX_SEND_TX_P2P_START_OKAY);
}

// Fetched a number of connections.
static void handle_check(callback_state& state, size_t connection_count,
    size_t node_count)
{
    state.output(format(BX_SEND_TX_P2P_CHECK_OKAY) % connection_count);
    if (connection_count >= node_count)
        state.stop();
}

// Send completed.
static void handle_sent(callback_state& state)
{
    state.output(format(BX_SEND_TX_P2P_SEND_OKAY) % now());
}

// Send tx to another Bitcoin node.
static void handle_send(callback_state& state, const std::error_code& code, 
    channel_ptr node, protocol& prot, tx_type& tx)
{
    // Set up callback handlers for sent and send.
    const auto sent_handler = [&state](const std::error_code& code)
    {
        state.handle_error(code, BX_SEND_TX_P2P_SEND_FAIL);
        handle_sent(state);
    };

    const auto send_handler = [&state](const std::error_code& code,
        channel_ptr node, protocol& prot, tx_type& tx)
    {
        state.handle_error(code, BX_SEND_TX_P2P_SETUP_FAIL);
        handle_send(state, code, node, prot, tx);
    };

    state.output(format(BX_SEND_TX_P2P_SETUP_OKAY) % transaction(tx));
    node->send(tx, sent_handler);
    prot.subscribe_channel(std::bind(send_handler, ph::_1, ph::_2,
        std::ref(prot), std::ref(tx)));
}

console_result send_tx_p2p::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& node_count = get_nodes_option();
    const auto& transactions = get_transactions_argument();

    // Set up shared state.
    callback_state state(error, output);

    // Set up callback handlers for start, connections check, send and stop.
    const auto start_handler = [&state](const std::error_code& code)
    {
        state.handle_error(code, BX_SEND_TX_P2P_START_FAIL);
        handle_start(state);
    };

    const auto check_handler = [&state](const std::error_code& code,
        size_t connection_count, size_t node_count)
    {
        state.handle_error(code, BX_SEND_TX_P2P_CHECK_FAIL);
        handle_check(state, connection_count, node_count);
    };

    const auto send_handler = [&state](const std::error_code& code,
        channel_ptr node, protocol& prot, tx_type& tx)
    {
        state.handle_error(code, BX_SEND_TX_P2P_SETUP_FAIL);
        handle_send(state, code, node, prot, tx);
    };

    const auto stop_handler = [](const std::error_code&)
    {
    };

    // Set up connections.
    async_client client(*this, 4);

    // Create dependencies for our protocol object.
    auto& pool = client.get_threadpool();
    hosts hst(pool);
    handshake hs(pool);
    network net(pool);

    // Set up protocol service.
    protocol prot(pool, hst, hs, net);
    prot.set_max_outbound(node_count * 6);


    // Perform node discovery if needed and then creating connections.
    prot.start(start_handler);

    // Create a subscription for each transaction.
    for (const tx_type& tx: transactions)
    {
        ++state;
        prot.subscribe_channel(
            std::bind(send_handler, ph::_1, ph::_2, std::ref(prot), tx));
    }

    // Catch C signals for stopping the program.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    // Check the connection count every 2 seconds.
    const auto work = [&prot, &node_count, &check_handler]
    {
        prot.fetch_connection_count(
            std::bind(check_handler, ph::_1, ph::_2, node_count));
    };

    client.poll(state.stopped(), 2000, work);
    prot.stop(stop_handler);
    
    return state.get_result();
}

// <define name="BX_SEND_TX_P2P_OUTPUT" value="%1% [%2%]: %3%" />
//static void output_to_file(std::ofstream& file, log_level level,
//    const std::string& domain, const std::string& body)
//{
//    if (!body.empty())
//        file << boost::format(BX_SEND_TX_P2P_OUTPUT) % level_repr(level) % body
//            << std::endl;
//}
//
//static void output_cerr_and_file(std::ofstream& file, log_level level,
//    const std::string& domain, const std::string& body)
//{
//    if (!body.empty())
//        std::cerr << boost::format(BX_SEND_TX_P2P_OUTPUT) % level_repr(level) %
//            body << std::endl;
//}

//// TODO: look into behavior if logging is invoked but log is not initialized.
//static void bind_logging(const boost::filesystem::path& debug,
//    const boost::filesystem::path& error)
//{
//    if (!debug.empty())
//    {
//        std::ofstream debug_file(debug.generic_string());
//        log_debug().set_output_function(
//            std::bind(output_to_file, std::ref(debug_file),
//            ph::_1, ph::_2, ph::_3));
//
//        log_info().set_output_function(
//            std::bind(output_to_file, std::ref(debug_file),
//            ph::_1, ph::_2, ph::_3));
//    }
//
//    if (!error.empty())
//    {
//        std::ofstream error_file(error.generic_string());
//        log_warning().set_output_function(
//            std::bind(output_to_file, std::ref(error_file),
//            ph::_1, ph::_2, ph::_3));
//
//        log_error().set_output_function(
//            std::bind(output_cerr_and_file, std::ref(error_file),
//            ph::_1, ph::_2, ph::_3));
//
//        log_fatal().set_output_function(
//            std::bind(output_cerr_and_file, std::ref(error_file),
//            ph::_1, ph::_2, ph::_3));
//    }
//}