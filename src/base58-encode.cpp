#include <iostream>
#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main(int argc, char** argv)
{
    std::string hex_str;
    if (argc == 1) {
        hex_str = read_stdin();
    }
    else if (argc == 2) 
    {
        hex_str = argv[1];
    }
    data_chunk data = decode_hex(hex_str);
    std::cout << encode_base58(data) << std::endl;
    return 0;
}

