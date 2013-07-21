#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>

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
    std::cout << "send-tx: Sending " << hash_transaction(tx) << std::endl;
    auto handle_send =
        [node](const std::error_code& ec)
        {
            if (ec)
                log_warning() << "Send failed: " << ec.message();
            else
                std::cout << "send-tx: Sent "
                    << time(nullptr) << std::endl;
            stopped = true;
        };
    node->send(tx, handle_send);
}

void load_tx(transaction_type& tx, const std::string& filename)
{
    std::ifstream infile(filename, std::ifstream::binary);
    // Get size of file.
    infile.seekg(0, infile.end);
    long size = infile.tellg();
    infile.seekg(0);
    // Allocate memory for file contents.
    data_chunk raw_tx(size);
    char* buffer = reinterpret_cast<char*>(raw_tx.data());
    infile.read(buffer, size);
    infile.close();
    // Deserialize tx.
    satoshi_load(raw_tx.begin(), raw_tx.end(), tx);
}

bool parse_port(uint16_t& port, const std::string& port_str)
{
    try
    {
        port = boost::lexical_cast<uint8_t>(port_str);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "send-tx: Bad port number provided" << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    if (argc < 2 || argc > 4)
    {
        std::cerr << "Usage: broadcast-tx FILENAME [HOST] [PORT]" << std::endl;
        return -1;
    }
    const std::string tx_filename = argv[1];
    transaction_type tx;
    load_tx(tx, tx_filename);
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
        sleep(2);
    // Safely close down.
    pool.stop();
    pool.join();
    return 0;
}

