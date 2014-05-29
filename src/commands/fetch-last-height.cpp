#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;

bool stopped = false;

void height_fetched(const std::error_code& ec, size_t height)
{
    if (ec)
    {
        std::cerr << "fetch-last-height: " << ec.message() << std::endl;
        stopped = true;
        return;
    }
    std::cout << height << std::endl;
    stopped = true;
}

int main()
{
    config_map_type config;
    load_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    fullnode.blockchain.fetch_last_height(height_fetched);
    while (!stopped)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    pool.stop();
    pool.join();
    return 0;
}

