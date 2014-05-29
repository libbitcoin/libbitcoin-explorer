#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

using namespace bc;
using namespace libwallet;

std::string dump_file(std::istream& in_file)
{
    std::istreambuf_iterator<char> it(in_file);
    std::istreambuf_iterator<char> end;
    return std::string(it, end);
}

int main()
{
    std::string seed = dump_file(std::cin);
    libwallet::deterministic_wallet wallet;
    if (!wallet.set_seed(seed))
    {
        std::cerr << "mpk: Error setting seed" << std::endl;
        return -1;
    }
    const data_chunk mpk = wallet.master_public_key();
    std::cout << mpk << std::endl;
    return 0;
}

