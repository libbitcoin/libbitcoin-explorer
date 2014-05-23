#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
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
    data_chunk bytes = decode_hex(hex_str);
    if (bytes.size() < 5) {
        std::cerr << "Error: Must be at least five bytes" << std::endl;
        return -1;
    }
    data_chunk rawdata(bytes.begin(), bytes.end() - 4);
    data_chunk rawchecksum(bytes.end() - 4, bytes.end());
    uint32_t checksum = bitcoin_checksum(rawdata);
    uint32_t my_checksum = from_little_endian<uint32_t>(rawchecksum.begin());
    if (checksum != my_checksum) {
        std::cerr << "Error: checksum does not match" << std::endl;
        return -1;
    }
    int vbyte = rawdata[0];
    data_chunk output(rawdata.begin()+1, rawdata.end());
    std::cout << output << " " << vbyte << std::endl;
    return 0;
}
