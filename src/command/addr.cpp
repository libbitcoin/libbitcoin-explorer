#include <iostream>
#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    elliptic_curve_key key;
    if (!read_public_or_private_key(key))
        return -1;
    payment_address address;
    set_public_key(address, key.public_key());
    if (argc == 2)
        address.set(atoi(argv[1]),address.hash());
    std::cout << address.encoded() << std::endl;
    return 0;
}

