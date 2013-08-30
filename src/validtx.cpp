#include <bitcoin/bitcoin.hpp>
#include <obelisk/client/interface.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;

bool stopped = false;

void tx_validated(const std::error_code& ec, const index_list& unconfirmed)
{
    std::cout << "Status: " << ec.message() << std::endl;
    for (size_t unconfirmed_index: unconfirmed)
        std::cout << "  Unconfirmed: " << unconfirmed_index << std::endl;
    stopped = true;
}

int main(int argc, char** argv)
{
    if (argc != 1 && argc != 2)
    {
        std::cout << "Usage: sx validtx FILENAME" << std::endl;
        return 1;
    }
    std::string filename;
    if (argc == 1)
        filename = "-";
    else
        filename = argv[1];
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
    config_map_type config;
    load_config(config);
    threadpool pool(1);
    fullnode_interface fullnode(pool, config["service"]);
    fullnode.transaction_pool.validate(tx, tx_validated);
    while (!stopped)
    {
        fullnode.update();
        sleep(0.1);
    }
    pool.stop();
    pool.join();
    return 0;
}

