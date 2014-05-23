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
    hd_private_key key;
    if (!key.set_serialized(encoded_key))
    {
        std::cerr << "hd-priv: error reading private key." << std::endl;
        return -1;
    }
    if (is_hard)
        index += libwallet::first_hardened_key;

    auto out = key.generate_private_key(index);
    if (!out.valid())
    {
        std::cerr << "hd-priv: error deriving child key." << std::endl;
        return -1;
    }
    std::cout << out.serialize() << std::endl;
    return 0;
}

