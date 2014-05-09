#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
using namespace libbitcoin;
using namespace libwallet;

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: sx stealth-uncover-secret EPHEM_PUBKEY "
            "SCAN_SECRET SPEND_SECRET" << std::endl;
        return -1;
    }
    ec_point ephem_pubkey = decode_hex(argv[1]);
    ec_secret scan_secret = decode_hash(argv[2]);
    ec_secret spend_secret = decode_hash(argv[3]);
    ec_secret secret = uncover_stealth_secret(
        ephem_pubkey, scan_secret, spend_secret);
    std::cout << secret << std::endl;
    return 0;
}

