#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include "util.hpp"
using namespace bc;
using namespace libwallet;

int main()
{
    // Read key from STDIN.
    std::string encoded_key = read_stdin();
    hd_public_key key;

    // First try loading private key.
    hd_private_key private_key;
    if (private_key.set_serialized(encoded_key))
        key = private_key;
    else if (!key.set_serialized(encoded_key))
    {
        std::cerr << "hd-pub: error reading key." << std::endl;
        return -1;
    }
    std::cout << key.address().encoded() << std::endl;
    return 0;
}

