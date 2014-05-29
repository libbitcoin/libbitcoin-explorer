#include "ec_util.hpp"

bool invoke(const int argc, const char* argv[])
{
    std::cerr << "sx: Not Implemented" << std::endl;

    // This is excluded because += is not yet defined for ec_point.
#ifdef false
    if (argc != 3)
    {
        std::cerr << "Usage: sx ec-add POINT POINT" << std::endl;
        return -1;
    }
    ec_point point_a, point_b;
    if (!set_ec_point(point_a, argv[1]))
    {
        std::cerr << "sx: Invalid point " << argv[1] << std::endl;
        return -1;
    }
    if (!set_ec_point(point_b, argv[2]))
    {
        std::cerr << "sx: Invalid point " << argv[2] << std::endl;
        return -1;
    }
    bool success = (point_a += point_b);
    if (!success)
    {
        std::cerr << "sx: Out of range." << std::endl;
        return -1;
    }
    std::cout << point_a << std::endl;
#endif

    return 0;
}

