#include "ec_util.hpp"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: sx ec-multiply INTEGER POINT" << std::endl;
        return -1;
    }
    ec_secret int_part;
    ec_point point_part;
    if (!ec_math_parse_args(argc, argv, int_part, point_part))
        return -1;
    bool success = ec_multiply(point_part, int_part);
    if (!success)
    {
        std::cerr << "sx: Out of range." << std::endl;
        return -1;
    }
    std::cout << point_part << std::endl;
    return 0;
}

