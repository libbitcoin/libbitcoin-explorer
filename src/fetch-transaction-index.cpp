#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;

bool stopped = false;

void index_fetched(const std::error_code& ec,
    size_t block_height, size_t index)
{
    if (ec)
    {
        std::cerr << "fetch-transaction: " << ec.message() << std::endl;
        stopped = true;
        return;
    }
    std::cout << "Height: " << block_height << std::endl;
    std::cout << "Index: " << index << std::endl;
    stopped = true;
}

int main(int argc, char** argv)
{
    std::string tx_hash_str;
    if (argc == 2)
        tx_hash_str = argv[1];
    else
        tx_hash_str = read_stdin();
    hash_digest tx_hash = decode_hex_digest<hash_digest>(tx_hash_str);
    config_map_type config;
    load_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    fullnode.blockchain.fetch_transaction_index(tx_hash, index_fetched);
    while (!stopped)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::seconds(100));
    }
    pool.stop();
    pool.join();
    return 0;
}

