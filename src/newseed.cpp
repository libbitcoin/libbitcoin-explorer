#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

using namespace bc;
using namespace libwallet;

int main()
{
    libwallet::deterministic_wallet wallet;
    wallet.new_seed();
    std::cout << wallet.seed() << std::endl;
    return 0;
}

