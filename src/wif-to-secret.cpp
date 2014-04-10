#include <iostream>
#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include "util.hpp"

using namespace bc;

int main(int argc, char** argv)
{
    std::string arg = read_stdin();
    auto h = libwallet::wif_to_secret(arg);
    if (h == null_hash)
    {
        std::cerr << "Invalid private key." << std::endl;
        return -1;
    }
    std::cout << h << std::endl;
    return 0;
}

