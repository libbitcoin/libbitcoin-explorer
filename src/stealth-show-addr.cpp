#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
using namespace bc;
using namespace libwallet;

void show_usage()
{
    std::cerr << "Usage: sx stealth-show-addr STEALTH_ADDRESS" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        show_usage();
        return -1;
    }
    const std::string stealth_str = argv[1];
    if (stealth_str == "--help" || stealth_str == "-h")
    {
        show_usage();
        return -1;
    }
    stealth_address addr;
    if (!addr.set_encoded(stealth_str))
    {
        std::cerr << "sx: Invalid stealth address." << std::endl;
        return -2;
    }
    // Now display fields.
    std::cout << "Options: ";
    if (addr.options() & stealth_address::reuse_key_option)
        std::cout << "reuse_key";
    else
        std::cout << "none";
    std::cout << std::endl;
    std::cout << "Scan pubkey: " << addr.scan_pubkey() << std::endl;
    std::cout << "Spend pubkeys:" << std::endl;
    for (const auto& pubkey: addr.spend_pubkeys())
        std::cout << "  " << pubkey << std::endl;
    std::cout << "Number required signatures: "
        << addr.number_signatures() << std::endl;
    // Display prefix.
    std::cout << "Prefix: "
        << (size_t)addr.prefix().number_bits << " "
        << addr.prefix().bitfield << std::endl;
    return 0;
}

