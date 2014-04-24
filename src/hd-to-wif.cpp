#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include "util.hpp"
using namespace bc;
using namespace libwallet;

int main()
{
    // Read key from STDIN.
    std::string encoded_key = read_stdin();
    hd_private_key key;
    if (!key.set_serialized(encoded_key))
    {
        std::cerr << "hd-priv: error reading private key." << std::endl;
        return -1;
    }
    secret_parameter secret = key.private_key();
    std::cout << secret_to_wif(secret) << std::endl;
    return 0;
}

