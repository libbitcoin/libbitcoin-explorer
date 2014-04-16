#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cerr << "sx pubkey [IS_COMPRESSED]" << std::endl;
        return -1;
    }
    int is_compressed = -1;
    if (argc == 2)
    {
        std::string flag_str = argv[1];
        boost::algorithm::to_lower(flag_str);
        if (flag_str == "1" || flag_str == "true" || flag_str == "yes")
            is_compressed = 1;
        else if (flag_str == "0" || flag_str == "false" || flag_str == "no")
            is_compressed = 0;
        else
        {
            std::cerr << "IS_COMPRESSED should be true or false." << std::endl;
            return -1;
        }
    }
    elliptic_curve_key key;
    if (!read_private_key(key, is_compressed))
        return -1;
    std::cout << key.public_key() << std::endl;
    return 0;
}

