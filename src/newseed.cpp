#include <bitcoin/bitcoin.hpp>
using namespace bc;

int main()
{
    deterministic_wallet wallet;
    wallet.new_seed();
    std::cout << wallet.seed() << std::endl;
    return 0;
}

