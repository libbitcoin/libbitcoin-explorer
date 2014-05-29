#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

using namespace libbitcoin;
using namespace libwallet;

bool invoke(const int argc, const char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: sx stealth-initiate EPHEM_SECRET SCAN_PUBKEY "
            "SPEND_PUBKEY" << std::endl;
        return -1;
    }
    ec_secret ephem_secret = decode_hash(argv[1]);
    ec_point scan_pubkey = decode_hex(argv[2]);
    ec_point spend_pubkey = decode_hex(argv[3]);
    ec_point pubkey = initiate_stealth(ephem_secret, scan_pubkey, spend_pubkey);
    std::cout << pubkey << std::endl;
    return 0;
}

