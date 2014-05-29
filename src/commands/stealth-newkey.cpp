#include <wallet/wallet.hpp>
#include "util.hpp"

using namespace libwallet;

int main()
{
    ec_secret scan_secret = generate_random_secret();
    ec_secret spend_secret = generate_random_secret();
    ec_point spend_pubkey = secret_to_public_key(spend_secret);

    stealth_address addr;
    addr.options = 0;
    addr.scan_pubkey = secret_to_public_key(scan_secret);
    addr.spend_pubkeys.push_back(spend_pubkey);
    addr.number_signatures = 1;

    std::cout << "Stealth address: " << addr.encoded() << std::endl;
    std::cout << "Scan secret: " << scan_secret << std::endl;
    std::cout << "Spend secret: " << spend_secret << std::endl;
    return 0;
}

