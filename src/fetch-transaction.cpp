#include <bitcoin/bitcoin.hpp>
#include <obelisk/client/interface.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;

bool stopped = false;

void tx_fetched(const std::error_code& ec, const transaction_type& tx)
{
    if (ec)
    {
        std::cerr << "fetch-transaction: " << ec.message() << std::endl;
        stopped = true;
        return;
    }
    data_chunk raw_tx(satoshi_raw_size(tx));
    satoshi_save(tx, raw_tx.begin());
    std::cout << raw_tx << std::endl;
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
    fullnode_interface fullnode(pool, config["service"]);
    fullnode.blockchain.fetch_transaction(tx_hash, tx_fetched);
    while (!stopped)
    {
        fullnode.update();
        sleep(0.1);
    }
    pool.stop();
    pool.join();
    return 0;
}

