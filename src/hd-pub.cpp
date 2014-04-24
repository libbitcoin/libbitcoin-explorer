#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include "util.hpp"
using namespace bc;
using namespace libwallet;

int main(int argc, char** argv)
{
    bool is_hard = false;
    uint32_t index = 0;
    if (!read_hd_command_args(argc, argv, is_hard, index))
        return -1;
    // Arguments now parsed. Read key from STDIN.
    std::string encoded_key = read_stdin();
    hd_public_key key;

    // First try loading private key.
    hd_private_key private_key;
    if (private_key.set_serialized(encoded_key))
        key = private_key;
    else if (!key.set_serialized(encoded_key))
    {
        std::cerr << "hd-pub: error reading key." << std::endl;
        return -1;
    }

    if (is_hard)
        index += libwallet::first_hardened_key;

    auto out = key.generate_public_key(index);
    if (!out.valid())
    {
        std::cerr << "hd-pub: error deriving child key." << std::endl;
        return -1;
    }
    std::cout << out.serialize() << std::endl;
    return 0;
}

