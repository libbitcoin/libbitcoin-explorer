#include <iostream>
#include <bitcoin/bitcoin.hpp>

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: sx validaddr ADDRESS" << std::endl;
        return -1;
    }
    payment_address payaddr;
    if (!payaddr.set_encoded(argv[1]))
    {
        std::cout << "Status: Invalid" << std::endl;
        return 1;
    }
    std::cout << "Status: Success" << std::endl;
    return 0;
}

