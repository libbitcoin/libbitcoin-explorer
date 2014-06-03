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
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/command/sendtx-p2p.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

void output_to_file(std::ofstream& file, log_level level,
    const std::string& domain, const std::string& body)
{
    if (body.empty())
        return;
    file << level_repr(level);
    if (!domain.empty())
        file << " [" << domain << "]";
    file << ": " << body << std::endl;
}
void output_cerr_and_file(std::ofstream& file, log_level level,
    const std::string& domain, const std::string& body)
{
    if (body.empty())
        return;
    std::ostringstream output;
    output << level_repr(level);
    if (!domain.empty())
        output << " [" << domain << "]";
    output << ": " << body;
    std::cerr << output.str() << std::endl;
}

// Needed for the C callback capturing the signals.
bool stopped = false;
void signal_handler(int sig)
{
    log_info() << "Caught signal: " << sig;
    stopped = true;
}

// Started protocol. Node discovery complete.
void handle_start(const std::error_code& ec);
// After number of connections is fetched, this completion handler is called
// and the number of connections is displayed.
void check_connection_count(
    const std::error_code& ec, size_t connection_count, size_t node_count);
// Send tx to another Bitcoin node.
void send_tx(const std::error_code& ec, channel_ptr node,
    protocol& prot, transaction_type& tx);

void handle_start(const std::error_code& ec)
{
    terminate_process_on_error(ec);
    log_debug() << "Started.";
}

void check_connection_count(
    const std::error_code& ec, size_t connection_count, size_t node_count)
{
    terminate_process_on_error(ec);
    log_debug() << connection_count << " CONNECTIONS";
    if (connection_count >= node_count)
        stopped = true;
}

void send_tx(const std::error_code& ec, channel_ptr node,
    protocol& prot, transaction_type& tx)
{
    terminate_process_on_error(ec);
    std::cout << "sendtx-p2p: Sending " << hash_transaction(tx) << std::endl;
    auto handle_send =
        [](const std::error_code& ec)
        {
            if (ec)
                log_warning() << "Send failed: " << ec.message();
            else
                std::cout << "sendtx-p2p: Sent "
                    << time(nullptr) << std::endl;
        };
    node->send(tx, handle_send);
    prot.subscribe_channel(
        std::bind(send_tx, _1, _2, std::ref(prot), std::ref(tx)));
}

bool parse_node_count(size_t& node_count, const std::string& count_str)
{
    try
    {
        node_count = boost::lexical_cast<size_t>(count_str);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "sign-input: Bad N provided" << std::endl;
        return false;
    }
    return true;
}

bool invoke(const int argc, const char* argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: sx sendtx-p2p FILENAME [NODE COUNT]" << std::endl;
        return -1;
    }
    const std::string filename = argv[1];
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
    size_t node_count = 2;
    if (argc == 3)
    {
        if (!parse_node_count(node_count, argv[2]))
            return -1;
    }

    std::ofstream outfile("debug.log"), errfile("error.log");
    log_debug().set_output_function(
        std::bind(output_to_file, std::ref(outfile), _1, _2, _3));
    log_info().set_output_function(
        std::bind(output_to_file, std::ref(outfile), _1, _2, _3));
    log_warning().set_output_function(
        std::bind(output_to_file, std::ref(errfile), _1, _2, _3));
    log_error().set_output_function(
        std::bind(output_cerr_and_file, std::ref(errfile), _1, _2, _3));
    log_fatal().set_output_function(
        std::bind(output_cerr_and_file, std::ref(errfile), _1, _2, _3));

    threadpool pool(4);
    // Create dependencies for our protocol object.
    hosts hst(pool);
    handshake hs(pool);
    network net(pool);
    // protocol service.
    protocol prot(pool, hst, hs, net);
    prot.set_max_outbound(node_count * 6);
    // Perform node discovery if needed and then creating connections.
    prot.start(handle_start);
    prot.subscribe_channel(
        std::bind(send_tx, _1, _2, std::ref(prot), std::ref(tx)));
    // Catch C signals for stopping the program.
    signal(SIGABRT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    // Check the connection count every 5 seconds.
    while (!stopped)
    {
        prot.fetch_connection_count(
            std::bind(check_connection_count, _1, _2, node_count));
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    const auto ignore_stop = [](const std::error_code&) {};
    prot.stop(ignore_stop);
    // Safely close down.
    pool.stop();
    pool.join();
    return 0;
}
