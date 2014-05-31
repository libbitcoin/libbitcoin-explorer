#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    std::string hex_str;
    uint8_t version_byte;
    if (argc == 1) {
        std::cin >> hex_str;
        int vb;
        std::cin >> vb;
            version_byte = vb;
    }
    else if (argc == 2) 
    {
        if (strlen(argv[1]) < 5) {
            version_byte = boost::lexical_cast<uint32_t>(argv[1]);
            hex_str = read_stdin();
        }
        else {
            version_byte = 0;
            hex_str = argv[1];
        }
    }
    else if (argc == 3) {
        version_byte = boost::lexical_cast<uint32_t>(argv[2]);
        hex_str = argv[1];
    }
    data_chunk bytes;
    bytes.push_back(version_byte);
    extend_data(bytes, decode_hex(hex_str));
    uint32_t checksum = bitcoin_checksum(bytes);
    extend_data(bytes, to_little_endian(checksum));

    std::cout << bytes << std::endl;
    return 0;
}

