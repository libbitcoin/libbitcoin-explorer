#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

using namespace bc;

int main()
{
    elliptic_curve_key key;
    key.new_keypair();
    secret_parameter secret = key.secret();
    std::cout << libwallet::secret_to_wif(secret) << std::endl;
    return 0;
}

