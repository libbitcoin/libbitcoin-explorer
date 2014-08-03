/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <sx/command/sendtx-p2p.hpp>

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/async_client.hpp>
#include <sx/define.hpp>
#include <sx/utility/utility.hpp>
#include <sx/serializer/item.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static bool stopped;
static console_result result;

static void output_to_file(std::ofstream& file, log_level level,
    const std::string& domain, const std::string& body)
{
    if (body.empty())
        return;

    file << boost::format(SX_SENDTX_P2P_OUTPUT) % level_repr(level) % body
        << std::endl;
}

static void output_cerr_and_file(std::ofstream& file, log_level level,
    const std::string& domain, const std::string& body)
{
    if (body.empty())
        return;

    std::cerr << boost::format(SX_SENDTX_P2P_OUTPUT) % level_repr(level) % body
        << std::endl;
}

static void signal_handler(int signal)
{
    log_info() << boost::format(SX_SENDTX_P2P_SIGNAL) % signal 
        /*<< std::endl*/;
    stopped = true;
}

// Started protocol. Node discovery complete.
static void handle_start(const std::error_code& error)
{
    if (error)
    {
        log_warning() << boost::format(SX_SENDTX_P2P_START_FAIL) % 
            error.message() /*<< std::endl*/;
        result = console_result::failure;
        stopped = true;
        return;
    }

    log_debug() << SX_SENDTX_P2P_START_OKAY;
}

// After number of connections is fetched, this completion handler is called
// and the number of connections is displayed.
static void check_connection_count(const std::error_code& error, 
    size_t connection_count, size_t node_count)
{
    if (error)
    {
        log_warning() << boost::format(SX_SENDTX_P2P_CHECK_FAIL) %
            error.message() /*<< std::endl*/;
        result = console_result::failure;
        stopped = true;
        return;
    }

    log_debug() << boost::format(SX_SENDTX_P2P_CHECK_OKAY) %
        connection_count /*<< std::endl*/;

    if (connection_count >= node_count)
        stopped = true;
}

// Send tx to another Bitcoin node.
static void send_tx(const std::error_code& error, channel_ptr node, 
    protocol& prot, transaction_type& tx)
{
    if (error)
    {
        log_warning() << boost::format(SX_SENDTX_P2P_SETUP_FAIL) %
            error.message() /*<< std::endl*/;
        result = console_result::failure;
        stopped = true;
        return;
    }

    std::cout << boost::format(SX_SENDTX_P2P_SETUP_OKAY) %
        item<bc::transaction_type>(tx) << std::endl;

    auto handle_send = [](const std::error_code& error)
    {
        if (error)
        {
            log_warning() << boost::format(SX_SENDTX_P2P_SEND_FAIL) %
                error.message() /*<< std::endl*/;
            result = console_result::failure;
            return;
        }

        std::cout << boost::format(SX_SENDTX_P2P_SEND_OKAY) % now()
            << std::endl;
    };

    node->send(tx, handle_send);
    prot.subscribe_channel(std::bind(send_tx, ph::_1, ph::_2, std::ref(prot),
        std::ref(tx)));
}

// TODO: look into behavior if logging is invoked but log is not initialized.
static void bind_logging(const boost::filesystem::path& debug, 
    const boost::filesystem::path& error)
{
    if (!debug.empty())
    {
        std::ofstream debug_file(debug.generic_string());
        log_debug().set_output_function(
            std::bind(output_to_file, std::ref(debug_file),
            ph::_1, ph::_2, ph::_3));

        log_info().set_output_function(
            std::bind(output_to_file, std::ref(debug_file),
            ph::_1, ph::_2, ph::_3));
    }

    if (!error.empty())
    {
        std::ofstream error_file(error.generic_string());
        log_warning().set_output_function(
            std::bind(output_to_file, std::ref(error_file),
            ph::_1, ph::_2, ph::_3));

        log_error().set_output_function(
            std::bind(output_cerr_and_file, std::ref(error_file),
            ph::_1, ph::_2, ph::_3));

        log_fatal().set_output_function(
            std::bind(output_cerr_and_file, std::ref(error_file),
            ph::_1, ph::_2, ph::_3));
    }
}

console_result sendtx_p2p::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto& debug_log = get_logging_debug_setting();
    const auto& error_log = get_logging_error_setting();
    const auto& node_count = get_nodes_option();
    const auto& transactions = get_transactions_argument();
    HANDLE_MULTIPLE_NOT_IMPLEMENTED(transactions);
    const transaction_type& tx = transactions.front();

    bind_logging(debug_log, error_log);

    stopped = false;
    result = console_result::okay;

    async_client client(*this, 4);

    // Create dependencies for our protocol object.
    auto& pool = client.get_threadpool();
    hosts hst(pool);
    handshake hs(pool);
    network net(pool);

    // protocol service.
    protocol prot(pool, hst, hs, net);
    prot.set_max_outbound(node_count * 6);

    // Perform node discovery if needed and then creating connections.
    prot.start(handle_start);
    prot.subscribe_channel(
        std::bind(send_tx, ph::_1, ph::_2, std::ref(prot), tx));

    // Catch C signals for stopping the program.
    signal(SIGABRT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    // Check the connection count every 2 seconds.
    const auto work = [&prot, &node_count]
    { 
        prot.fetch_connection_count(
            std::bind(check_connection_count, ph::_1, ph::_2, node_count));
    };

    client.poll(stopped, 2000, work);
    const auto ignore_stop = [](const std::error_code&) {};
    prot.stop(ignore_stop);

    return result;
}
