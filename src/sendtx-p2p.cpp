#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

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

// We don't have a database open, and aren't doing any critical file
// operations so we aren't worried about exiting suddenly.
void check_error(const std::error_code& ec)
{
    if (!ec)
        return;
    log_fatal() << ec.message();
    exit(-1);
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
    check_error(ec);
    log_debug() << "Started.";
}

void check_connection_count(
    const std::error_code& ec, size_t connection_count, size_t node_count)
{
    check_error(ec);
    log_debug() << connection_count << " CONNECTIONS";
    if (connection_count >= node_count)
        stopped = true;
}

void send_tx(const std::error_code& ec, channel_ptr node,
    protocol& prot, transaction_type& tx)
{
    check_error(ec);
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

int main(int argc, char** argv)
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
        sleep(2);
    }
    auto ignore_stop = [](const std::error_code&) {};
    prot.stop(ignore_stop);
    // Safely close down.
    pool.stop();
    pool.join();
    return 0;
}

