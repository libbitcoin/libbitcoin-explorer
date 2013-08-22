#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"
using namespace bc;

int main(int argc, char** argv)
{
    if (argc > 3)
    {
        std::cerr << "Usage: encode-addr ADDRESS [version_byte] " << std::endl;
        return -1;
    }

    std::string addr_str;
    uint8_t version_byte = 0;

    if (argc == 1)
    {
        addr_str = read_stdin();
    }
    else if (argc == 2) 
    {
        if (strlen(argv[1]) > 5)
            addr_str = argv[1];
        else
        {
            version_byte = boost::lexical_cast<uint32_t>(argv[1]);
            addr_str = read_stdin();
        }
    }
    else
    {
        BITCOIN_ASSERT(argc == 3);
        version_byte = boost::lexical_cast<uint32_t>(argv[2]);
        addr_str = argv[1];
    }

    data_chunk data = decode_hex(addr_str);
    short_hash hashdata;
    std::copy(data.begin(), data.end(), hashdata.begin());
    payment_address addr;

    addr.set(version_byte, hashdata);
    
    std::cout << addr.encoded() << std::endl;
    return 0;
}
