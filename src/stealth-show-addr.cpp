#include <bitcoin/bitcoin.hpp>
using namespace bc;

class stealth_address
{
public:
    typedef std::vector<data_chunk> pubkey_list;
    enum
    {
        reuse_key_option = 0x01
    };

    uint8_t options() const;
    const data_chunk& scan_pubkey() const;
    const pubkey_list& spend_pubkeys() const;
    size_t number_signatures() const;
    const stealth_prefix& prefix() const;

    bool set_encoded(const std::string& encoded_address);

private:
    uint8_t options_ = 0;
    data_chunk scan_pubkey_;
    pubkey_list spend_pubkeys_;
    size_t number_signatures_ = 0;
    stealth_prefix prefix_{0, 0};
};

constexpr uint8_t stealth_version_byte = 0x2a;

uint8_t stealth_address::options() const
{
    return options_;
}
const data_chunk& stealth_address::scan_pubkey() const
{
    return scan_pubkey_;
}
const stealth_address::pubkey_list& stealth_address::spend_pubkeys() const
{
    return spend_pubkeys_;
}
size_t stealth_address::number_signatures() const
{
    return number_signatures_;
}
const stealth_prefix& stealth_address::prefix() const
{
    return prefix_;
}

bool stealth_address::set_encoded(const std::string& encoded_address)
{
    data_chunk raw_addr = decode_base58(encoded_address);
    if (!verify_checksum(raw_addr))
        return false;
    BITCOIN_ASSERT(raw_addr.size() >= 4);
    auto checksum_begin = raw_addr.end() - 4;
    // Delete checksum bytes.
    raw_addr.erase(checksum_begin, raw_addr.end());
    // https://wiki.unsystem.net/index.php/DarkWallet/Stealth#Address_format
    // [version] [options] [scan_key] [N] ... [Nsigs] [prefix_length] ...
    size_t estimated_data_size = 1 + 1 + 33 + 1 + 1 + 1;
    BITCOIN_ASSERT(raw_addr.size() >= estimated_data_size);
    auto iter = raw_addr.begin();
    uint8_t version = *iter;
    if (version != stealth_version_byte)
        return false;
    ++iter;
    options_ = *iter;
    ++iter;
    auto scan_key_begin = iter;
    iter += 33;
    scan_pubkey_ = data_chunk(scan_key_begin, iter);
    uint8_t number_spend_pubkeys = *iter;
    ++iter;
    estimated_data_size += number_spend_pubkeys * 33;
    BITCOIN_ASSERT(raw_addr.size() >= estimated_data_size);
    for (size_t i = 0; i < number_spend_pubkeys; ++i)
    {
        auto spend_key_begin = iter;
        iter += 33;
        spend_pubkeys_.emplace_back(data_chunk(spend_key_begin, iter));
    }
    number_signatures_ = *iter;
    ++iter;
    prefix_.number_bits = *iter;
    ++iter;
    size_t number_bitfield_bytes = 0;
    if (prefix_.number_bits > 0)
        number_bitfield_bytes = prefix_.number_bits / 8 + 1;
    estimated_data_size += number_bitfield_bytes;
    BITCOIN_ASSERT(raw_addr.size() >= estimated_data_size);
    // Unimplemented currently!
    BITCOIN_ASSERT(number_bitfield_bytes == 0);
    return true;
}

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

