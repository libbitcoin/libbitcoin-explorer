#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
using namespace libbitcoin;
using namespace libwallet;

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: sx stealth-uncover EPHEM_PUBKEY SCAN_SECRET "
            "SPEND_PUBKEY" << std::endl;
        return -1;
    }
    ec_point ephem_pubkey = decode_hex(argv[1]);
    ec_secret scan_secret = decode_hex_digest<ec_secret>(argv[2]);
    ec_point spend_pubkey = decode_hex(argv[3]);
    ec_point pubkey = uncover_stealth(ephem_pubkey, scan_secret, spend_pubkey);
    std::cout << pubkey << std::endl;
    return 0;
}

