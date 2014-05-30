#include <iostream>
#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    std::string b58_str;
    if (argc == 1) {
        b58_str = read_stdin();
    }
    else if (argc == 2) 
    {
        b58_str = argv[1];
    }
    data_chunk data = decode_base58(b58_str);
    std::cout << encode_hex(data) << std::endl;
    return 0;
}

