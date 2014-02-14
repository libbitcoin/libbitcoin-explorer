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
        return;
    }
    for (const blockchain::stealth_row& row: stealth_results)
        log_debug() << "ephemkey: " << row.ephemkey
            << " address: " << row.address.encoded()
            << " tx_hash: " << row.transaction_hash;
    stopped = true;
}

int main(int argc, char** argv)
{
    if (argc != 3 && argc != 4)
    {
        std::cerr << "Usage: fetch-stealth NUMBER_BITS BITFIELD [FROM_HEIGHT]"
            << std::endl;
        return -1;
    }
    size_t from_height = 0;
    if (argc == 4)
        from_height = boost::lexical_cast<size_t>(argv[3]);
    stealth_prefix prefix;
    prefix.number_bits = boost::lexical_cast<int>(argv[1]);
    data_chunk bitfield_bytes = decode_hex(argv[2]);
    prefix.bitfield = cast_chunk<uint32_t>(bitfield_bytes);
    // Start Obelisk
    config_map_type config;
    load_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"]);
    // Perform query.
    fullnode.blockchain.fetch_stealth(prefix,
        std::bind(stealth_fetched, _1, _2), from_height);
    while (!stopped)
    {
        fullnode.update();
        usleep(100000);
    }
    pool.stop();
    pool.join();
    return 0;
}

