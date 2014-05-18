#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

void history_fetched(const std::error_code& ec,
    const blockchain::history_list& history)
{
    if (ec)
    {
        std::cerr << "history: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    for (const auto& row: history)
    {
        int64_t value = row.value;
        std::cout << row.output.hash << " " << value << std::endl;
        if (row.spend.hash != null_hash)
            std::cout << row.spend.hash << " " << -value << std::endl;
    }
}

void subscribed(const std::error_code& ec, const obelisk::worker_uuid& worker)
{
    if (ec)
    {
        std::cerr << "Error: " << ec.message() << std::endl;
        return;
    }
    std::cout << "Subscribed." << std::endl;
    //fullnode.address.fetch_history(payaddr,
    //    std::bind(history_fetched, _1, _2), 0, worker);
}

void new_update(const std::error_code& ec,
    size_t height, const hash_digest& block_hash, const transaction_type& tx)
{
    std::cout << "Update " << hash_transaction(tx)
        << " [ #" << height << " " << block_hash << " ]" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: sx monitor PREFIX" << std::endl;
        return -1;
    }
    std::cerr << std::endl;
    std::cerr << "**************************************" << std::endl;
    std::cerr << "Warning: this command is experimental." << std::endl;
    std::cerr << "**************************************" << std::endl;
    std::cerr << std::endl;
    std::string bits = argv[1];
    obelisk::address_prefix prefix(bits);
    config_map_type config;
    load_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    fullnode.address.subscribe(prefix, new_update, subscribed);
    while (true)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    pool.stop();
    pool.join();
    return 0;
}

