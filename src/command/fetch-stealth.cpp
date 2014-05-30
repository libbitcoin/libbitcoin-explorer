#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include "config.hpp"

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

bool stopped = false;

void stealth_fetched(const std::error_code& ec,
    const blockchain::stealth_list& stealth_results)
{
    if (ec)
    {
        log_error() << "Stealth fetch failed: " << ec.message();
        stopped = true;
        return;
    }
    for (const blockchain::stealth_row& row: stealth_results)
        std::cout << "ephemkey: " << row.ephemkey
            << " address: " << row.address.encoded()
            << " tx_hash: " << row.transaction_hash << std::endl;
    stopped = true;
}

bool invoke(const int argc, const char* argv[])
{
    if (argc > 3)
    {
        std::cerr << "Usage: fetch-stealth BITFIELD [FROM_HEIGHT]"
            << std::endl;
        return -1;
    }
    size_t from_height = 0;
    if (argc == 3)
        from_height = boost::lexical_cast<size_t>(argv[2]);
    stealth_prefix prefix;
    if (argc >= 2)
        prefix = stealth_prefix(std::string(argv[1]));
    // Start Obelisk
    config_map_type config;
    load_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    // Perform query.
    fullnode.blockchain.fetch_stealth(prefix,
        std::bind(stealth_fetched, _1, _2), from_height);
    while (!stopped)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    pool.stop();
    pool.join();
    return 0;
}

