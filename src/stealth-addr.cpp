#include <bitcoin/bitcoin.hpp>
using namespace bc;

int main(int argc, char** argv)
{
    typedef std::vector<std::string> string_list;
    string_list args;
    for (size_t i = 1; i < argc; ++i)
        args.push_back(argv[i]);
    // Check for optional arguments.
    bool reuse_address = false;
    for (auto it = args.begin(); it != args.end(); ++it)
        if (*it == "--reuse-key" || *it == "-r")
        {
            args.erase(it);
            break;
        }
    // Read scan pubkey.
    if (args.empty())
    {
        std::cout << "sx: scan pubkey must be provided." << std::endl;
        return -1;
    }
    const data_chunk scan_pubkey = decode_hex(args[0]);
    args.erase(args.begin());
    // Remaining keys are spend_pubkeys.
    typedef std::vector<data_chunk> pubkey_list;
    pubkey_list spend_pubkeys;
    for (const auto& arg: args)
        spend_pubkeys.emplace_back(decode_hex(arg));
    // Now we have the data.
    // Construct actual address.
    // https://wiki.unsystem.net/index.php/DarkWallet/Stealth#Address_format
    data_chunk raw_addr;
    // version byte.
    raw_addr.push_back({0x2a});
    // options byte.
    uint8_t options_bitfield = 0;
    if (reuse_address)
        options_bitfield &= 1;
    raw_addr.push_back(options_bitfield);
    extend_data(raw_addr, scan_pubkey);
    uint8_t number_keys = spend_pubkeys.size();
    raw_addr.push_back(number_keys);
    for (const auto& pubkey: spend_pubkeys)
        extend_data(raw_addr, pubkey);
    // For now put number_sigs = number_keys
    // Allow configuring this later.
    uint8_t number_sigs = number_keys;
    raw_addr.push_back(number_sigs);
    // Prefix filter currently unused.
    // Allow configuring this later.
    raw_addr.push_back({0x00});
    uint32_t checksum = bitcoin_checksum(raw_addr);
    append_checksum(raw_addr);
    const std::string stealth_addr = encode_base58(raw_addr);
    std::cout << stealth_addr << std::endl;
    return 0;
}

