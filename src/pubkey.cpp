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
    std::cout << key.public_key() << std::endl;
    return 0;
}

