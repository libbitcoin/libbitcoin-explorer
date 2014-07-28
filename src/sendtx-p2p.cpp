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
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

// Needed for the C callback capturing the signals.
static bool stopped = false;

static void output_to_file(std::ofstream& file, log_level level,
    const std::string& domain, const std::string& body)
{
    if (body.empty())
        return;

    file << level_repr(level);
    if (!domain.empty())
        file << " [" << domain << "]";

    file << ": " << body << std::endl;
}

static void output_cerr_and_file(std::ofstream& file, log_level level,
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

static void signal_handler(int sig)
{
    log_info() << "Caught signal: " << sig;
    stopped = true;
}

// Started protocol. Node discovery complete.
static void handle_start(const std::error_code& error)
{
    terminate_process_on_error(error);
    log_debug() << "Started.";
}

// After number of connections is fetched, this completion handler is called
// and the number of connections is displayed.
static void check_connection_count(const std::error_code& error, 
    size_t connection_count, size_t node_count)
{
    terminate_process_on_error(error);
    log_debug() << connection_count << " CONNECTIONS";
    if (connection_count >= node_count)
        stopped = true;
}

// Send tx to another Bitcoin node.
static void send_tx(const std::error_code& error, channel_ptr node, 
    protocol& prot, transaction_type& tx)
{
    terminate_process_on_error(error);
    std::cout << "sendtx-p2p: Sending " << hash_transaction(tx) << std::endl;
    auto handle_send =
        [](const std::error_code& error)
        {
            if (error)
                log_warning() << "Send failed: " << error.message();
            else
                std::cout << "sendtx-p2p: Sent " << time(nullptr) << std::endl;
        };
    node->send(tx, handle_send);
    prot.subscribe_channel(std::bind(send_tx, _1, _2, std::ref(prot), 
        std::ref(tx)));
}

console_result sendtx_p2p::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 2, 3))
        return console_result::failure;

    transaction_type tx;
    const std::string filename(get_filename(argc, argv));
    if (!load_satoshi_item<transaction_type>(tx, filename, std::cin))
    {
        std::cerr << "sx: Deserializing transaction failed." << std::endl;
        return console_result::failure;
    }

    size_t node_count = 2;
    if (argc > 2)
    {
        if (!parse(node_count, argv[2]))
        {
            std::cerr << "sign-input: Bad N provided" << std::endl;
            return console_result::failure;
        }
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

    // Check the connection count every 2 seconds.
    while (!stopped)
    {
        prot.fetch_connection_count(
            std::bind(check_connection_count, _1, _2, node_count));
        sleep_ms(2000);
    }

    const auto ignore_stop = [](const std::error_code&) {};
    prot.stop(ignore_stop);
    pool.stop();
    pool.join();
    return console_result::okay;
}
