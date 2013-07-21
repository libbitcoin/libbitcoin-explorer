#include <iostream>
#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main()
{
    elliptic_curve_key key;
    if (!read_private_key(key))
        return -1;
    payment_address address;
    if (!set_public_key(address, key.public_key()))
    {
        std::cerr << "Set public key on address failed." << std::endl;
        return -1;
    }
    std::cout << address.encoded() << std::endl;
    return 0;
}

