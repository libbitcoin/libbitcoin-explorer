#include "ec_util.hpp"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: sx ec-multiply INTEGER POINT" << std::endl;
        return -1;
    }
    ec_secret int_part = null_hash;
    ec_point point_part;
    for (size_t i = 1; i < argc; ++i)
    {
        const auto arg = argv[i];
        if (set_ec_secret(int_part, arg))
            continue;
        if (set_ec_point(point_part, arg))
            continue;
    }
    if (int_part == null_hash || point_part.empty())
    {
        std::cerr << "sx: Unable to read input values." << std::endl;
        return -1;
    }
    bool success = (point_part += int_part);
    if (!success)
    {
        std::cerr << "sx: Out of range." << std::endl;
        return -1;
    }
    std::cout << point_part << std::endl;
    return 0;
}

