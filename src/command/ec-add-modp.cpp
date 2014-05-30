#include "ec_util.hpp"

bool invoke(const int argc, const char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: sx ec-add-modp INTEGER INTEGER" << std::endl;
        return -1;
    }
    ec_secret secret_a, secret_b;
    if (!set_ec_secret(secret_a, argv[1]))
    {
        std::cerr << "sx: Invalid secret " << argv[1] << std::endl;
        return -1;
    }
    if (!set_ec_secret(secret_b, argv[2]))
    {
        std::cerr << "sx: Invalid secret " << argv[2] << std::endl;
        return -1;
    }
    if (!ec_add(secret_a, secret_b))
    {
        std::cerr << "sx: Error adding numbers." << std::endl;
        return -1;
    }
    std::cout << secret_a << std::endl;
    return 0;
}

