#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main()
{
    std::string hex_script = read_stdin();
    script_type bip16_script = parse_script(decode_hex(hex_script));
    payment_address payaddr;
    set_script(payaddr, bip16_script);
    std::cout << payaddr.encoded() << std::endl;
    return 0;
}

