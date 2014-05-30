#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

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

void send_tx(const std::error_code& ec, channel_ptr node, transaction_type& tx)
{
    check_error(ec);
    std::cout << "sendtx: Sending " << hash_transaction(tx) << std::endl;
    auto handle_send =
        [node](const std::error_code& ec)
        {
            if (ec)
                log_warning() << "Send failed: " << ec.message();
            else
                std::cout << "sendtx: Sent "
                    << time(nullptr) << std::endl;
            stopped = true;
        };
    node->send(tx, handle_send);
}

bool parse_port(uint16_t& port, const std::string& port_str)
{
    try
    {
        port = boost::lexical_cast<uint16_t>(port_str);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "sendtx: Bad port number provided" << std::endl;
        return false;
    }
    return true;
}

bool invoke(const int argc, const char* argv[])
{
    if (argc < 2 || argc > 4)
    {
        std::cerr << "Usage: sx sendtx-node FILENAME [HOST] [PORT]"
            << std::endl;
        return -1;
    }
    const std::string filename = argv[1];
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
    std::string hostname = "localhost";
    if (argc >= 3)
        hostname = argv[2];
    uint16_t port = 8333;
    BITCOIN_ASSERT(argc <= 4);
    if (argc == 4)
        if (!parse_port(port, argv[3]))
            return -1;

    threadpool pool(4);
    // Create dependencies for our protocol object.
    handshake shake(pool);
    network net(pool);
    connect(shake, net, hostname, port,
        std::bind(send_tx, _1, _2, std::ref(tx)));
    while (!stopped)
        std::this_thread::sleep_for(std::chrono::seconds(2));
    // Safely close down.
    pool.stop();
    pool.join();
    return 0;
}
    
