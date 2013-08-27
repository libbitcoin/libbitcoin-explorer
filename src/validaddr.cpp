#include <bitcoin/bitcoin.hpp>
using namespace bc;

int main(int argc, char** argv)
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

