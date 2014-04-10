#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main(int argc, char** argv)
{
    if (argc != 2 && argc != 1)
    {
        std::cerr << "Usage: decode-addr ADDRESS" << std::endl;
        return -1;
    }
    std::string addr_str;
    if (argc == 1)
        addr_str = read_stdin();
    else
        addr_str = argv[1];
    payment_address addr;
    if (!addr.set_encoded(addr_str))
    {
        std::cerr << "decode-addr: Bad address '"
            << addr_str << "'." << std::endl;
        return -1;
    }
    std::cout << addr.hash() << std::endl;
    return 0;
}

