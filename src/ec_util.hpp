#include <bitcoin/bitcoin.hpp>
using namespace bc;

bool set_ec_secret(ec_secret& secret, const std::string& arg)
{
    secret = decode_hex_digest<ec_secret>(arg);
    return secret != null_hash;
}
bool set_ec_point(ec_point& point, const std::string& arg)
{
    //if (arg == "G")
    ec_point result = decode_hex(arg);
    if (result.size() != ec_compressed_size)
       return false;
    if (result[0] != 0x02 && result[0] != 0x03)
       return false;
    point = result;
    return true;
}

