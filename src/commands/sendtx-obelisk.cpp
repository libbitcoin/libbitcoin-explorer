#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;

bool stopped = false;

void handle_broadcast(const std::error_code& ec)
{
    std::cout << "Status: " << ec.message() << std::endl;
    stopped = true;
}

bool invoke(const int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: sendtx-obelisk FILENAME" << std::endl;
        return -1;
    }
    const std::string filename = argv[1];
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
    config_map_type config;
    load_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    fullnode.protocol.broadcast_transaction(tx, handle_broadcast);
    while (!stopped)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    pool.stop();
    pool.join();
    return 0;
}

