#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main()
{
    std::string data = read_stdin();
    const short_hash hash =
        bitcoin_short_hash(data_chunk(data.begin(), data.end()));
    std::cout << hash << std::endl;
}

