#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/client/interface.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;

bool stopped = false;

void block_header_fetched(const std::error_code& ec,
    const block_header_type& blk_header)
{
    if (ec)
    {
        std::cerr << "fetch-block-header: " << ec.message() << std::endl;
        stopped = true;
        return;
    }
    data_chunk raw_blk_header(satoshi_raw_size(blk_header));
    satoshi_save(blk_header, raw_blk_header.begin());
    std::cout << raw_blk_header << std::endl;
    stopped = true;
}

int main(int argc, char** argv)
{
    std::string index_str;
    if (argc == 2)
        index_str = argv[1];
    else
        index_str = read_stdin();
    config_map_type config;
    load_config(config);
    threadpool pool(1);
    fullnode_interface fullnode(pool, config["service"]);
    // Try first to interpret index as hash, if that fails then
    // interpret the index as a height instead.
    hash_digest blk_hash = decode_hex_digest<hash_digest>(index_str);
    if (blk_hash == null_hash)
    {
        size_t height = 0;
        boost::algorithm::trim(index_str);
        try
        {
            height = boost::lexical_cast<size_t>(index_str);
        }
        catch (const boost::bad_lexical_cast&)
        {
            std::cerr << "fetch-block-header: Bad index provided." << std::endl;
            return -1;
        }
        fullnode.blockchain.fetch_block_header(height, block_header_fetched);
    }
    else
    {
        fullnode.blockchain.fetch_block_header(blk_hash, block_header_fetched);
    }
    while (!stopped)
    {
        fullnode.update();
        sleep(0.1);
    }
    pool.stop();
    pool.join();
    return 0;
}

