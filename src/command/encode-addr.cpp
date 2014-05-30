#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    if (argc > 3)
    {
        std::cerr << "Usage: sx encode-addr HASH [VERSION] " << std::endl;
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

    short_hash hashdata = decode_short_hash(addr_str);
    if (hashdata == null_short_hash)
    {
        std::cerr << "Incorrect HASH passed in." << std::endl;
        return -1;
    }

    payment_address addr(version_byte, hashdata);
    std::cout << addr.encoded() << std::endl;
    return 0;
}
