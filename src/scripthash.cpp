#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main()
{
    std::string hex_script = read_stdin();
    script bip16_script = parse_script(decode_hex(hex_script));
    payment_address payaddr;
    if (!set_script(payaddr, bip16_script))
    {
        std::cerr << "scripthash: Error setting script for address."
            << std::endl;
        return -1;
    }
    std::cout << payaddr.encoded() << std::endl;
    return 0;
}

