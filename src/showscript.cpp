#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main()
{
    std::string hex_script = read_stdin();
    script_type scr = parse_script(decode_hex(hex_script));
    std::cout << pretty(scr) << std::endl;
    return 0;
}

