#include <bitcoin/bitcoin.hpp>
using namespace bc;

bool set_ec_secret(ec_secret& secret, const std::string& arg)
{
    ec_secret result = decode_hex_digest<ec_secret>(arg);
    if (result == null_hash)
        return false;
    secret = result;
    return true;
}
bool set_ec_point(ec_point& point, const std::string& arg)
{
    ec_point result = decode_hex(arg);
    if (result.size() != ec_compressed_size)
       return false;
    if (result[0] != 0x02 && result[0] != 0x03)
       return false;
    point = result;
    return true;
}

bool ec_math_parse_args(
    int argc, char** argv, ec_secret& secret, ec_point& point)
{
    for (size_t i = 1; i < argc; ++i)
    {
        const auto arg = argv[i];
        if (set_ec_secret(secret, arg))
            continue;
        if (set_ec_point(point, arg))
            continue;
    }
    if (secret == null_hash || point.empty())
    {
        std::cerr << "sx: Unable to read input values." << std::endl;
        return false;
    }
    return true;
}

