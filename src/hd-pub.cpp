#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include "util.hpp"

using namespace bc;
using namespace libwallet;

int main(int argc, char** argv)
{
    // Special case - read private key from STDIN and
    // convert it to a public key.
    if (argc == 1)
    {
        std::string encoded_key = read_stdin();
        hd_private_key private_key;
        if (!private_key.set_serialized(encoded_key))
        {
            std::cerr << "sx: Error reading private key." << std::endl;
            return -1;
        }
        const hd_public_key public_key = private_key;
        std::cout << public_key.serialize() << std::endl;
        return 0;
    }
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
        std::cerr << "sx: Error reading key." << std::endl;
        return -1;
    }

    if (!private_key.valid() && is_hard)
    {
        std::cerr << "sx: Cannot use --hard with public keys."
            << std::endl;
        return -1;
    }

    hd_public_key out;
    // You must use the private key to generate --hard keys.
    if (is_hard)
    {
        index += libwallet::first_hardened_key;
        out = private_key.generate_public_key(index);
    }
    else
        out = key.generate_public_key(index);

    if (!out.valid())
    {
        std::cerr << "sx: Error deriving child key." << std::endl;
        return -1;
    }
    std::cout << out.serialize() << std::endl;
    return 0;
}

