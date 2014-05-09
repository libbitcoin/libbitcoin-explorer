#include "util.hpp"

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cerr << "Usage: sx sha256 DATA" << std::endl;
        return -1;
    }
    std::string arg;
    if (argc == 2)
        arg = argv[1];
    else
        arg = read_stdin();
    data_chunk data = decode_hex(arg);
    if (data.empty())
    {
        std::cerr << "sx: Non-hex input data." << std::endl;
        return -1;
    }
    std::cout << sha256_hash(data) << std::endl;
    return 0;
}

