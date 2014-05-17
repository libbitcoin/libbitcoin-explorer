#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include "config.hpp"

using namespace bc;
using namespace libwallet;

data_chunk random_bytes(size_t size)
{
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<uint8_t> uniform_dist(0, 255);

    data_chunk result;
    for (size_t i = 0; i < size; ++i)
        result.push_back(uniform_dist(engine));
    return result;
}

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cerr << "Usage: sx hd-seed [ENTROPY]" << std::endl;
        return -1;
    }
    data_chunk entropy;
    if (argc == 2)
        entropy = decode_hex(argv[1]);
    else
        entropy = random_bytes(32);

    config_map_type config;
    load_config(config);

    bool testnet;
    if (config["testnet"] == "true")
	testnet = true;
    else
	testnet = false;

    hd_private_key hd_key(entropy, testnet);
    std::cout << hd_key.serialize() << std::endl;
    return 0;
}

