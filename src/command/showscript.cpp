#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main()
{
    data_chunk raw_script = decode_hex(read_stdin());
    script_type script;
    try
    {
        script = parse_script(raw_script);
    }
    catch (end_of_stream)
    {
        std::cerr << "showscript: Error: Bad script." << std::endl;
        return -1;
    }
    std::cout << pretty(script) << std::endl;
    return 0;
}

