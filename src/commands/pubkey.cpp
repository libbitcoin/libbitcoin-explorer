#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    if (argc > 2)
    {
        std::cerr << "Usage: sx pubkey [--uncompressed|--compressed]" << std::endl;
        return -1;
    }
    int is_compressed = -1;
    if (argc == 2)
    {
        std::string flag_str = argv[1];
        boost::algorithm::to_lower(flag_str);
        if (flag_str == "1" || flag_str == "true" || flag_str == "yes" ||
            flag_str == "--compressed" || flag_str == "-c")
            is_compressed = 1;
        else if (flag_str == "0" || flag_str == "false" || flag_str == "no" ||
            flag_str == "--uncompressed" || flag_str == "-u")
            is_compressed = 0;
        else
        {
            std::cerr << "IS_COMPRESSED should be true or false." << std::endl;
            return -1;
        }
    }
    std::string arg = read_stdin();
    elliptic_curve_key key;
    if (!read_private_key(key, arg, is_compressed))
    {
        // Try reading it as a public key instead.
        data_chunk pubkey = decode_hex(arg);
        if (pubkey.empty())
        {
            std::cerr << "Invalid private or public key." << std::endl;
            return -1;
        }
        // OK, it's a public key.
        if (!key.set_public_key(pubkey))
        {
            std::cerr << "Invalid public key." << std::endl;
            return -1;
        }
        key.set_compressed(is_compressed >= 0);
    }
    std::cout << key.public_key() << std::endl;
    return 0;
}

