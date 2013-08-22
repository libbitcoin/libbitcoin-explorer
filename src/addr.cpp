#include <iostream>
#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

bool read_public_or_private_key(elliptic_curve_key& key)
{
    std::string arg = read_stdin();
    if (read_private_key(key, arg))
        return true;
    data_chunk pubkey = decode_hex(arg);
    if (key.set_public_key(pubkey))
        return true;
    std::cerr << "Invalid public or private key." << std::endl;
    return false;
}

int main()
{
    elliptic_curve_key key;
    if (!read_public_or_private_key(key))
        return -1;
    payment_address address;
    set_public_key(address, key.public_key());
    std::cout << address.encoded() << std::endl;
    return 0;
}

