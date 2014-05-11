#ifndef SX_UTIL_HPP
#define SX_UTIL_HPP

#include <iostream>
#include <random>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

using namespace bc;

bool load_tx(transaction_type& tx, const std::string& filename)
{
    std::ostringstream contents;
    if (filename == "-")
    {
        std::istreambuf_iterator<char> first(std::cin);
        std::istreambuf_iterator<char> last;
        contents << std::string(first, last);
    }
    else
    {
        std::ifstream infile(filename, std::ifstream::binary);
        if (!infile)
        {
            std::cerr << "showtx: Bad file." << std::endl;
            return false;
        }
        contents << infile.rdbuf();
    }
    data_chunk raw_tx = decode_hex(contents.str());
    try
    {
        satoshi_load(raw_tx.begin(), raw_tx.end(), tx);
    }
    catch (end_of_stream)
    {
        std::cerr << "showtx: Deserializing transaction failed." << std::endl;
        return false;
    }
    return true;
}

std::string read_stdin()
{
    std::istreambuf_iterator<char> first(std::cin);
    std::istreambuf_iterator<char> last;
    std::string result(first, last);
    boost::algorithm::trim(result);
    return result;
}

bool read_private_key(elliptic_curve_key& key, const std::string& arg,
    int is_compressed=-1)
{
    secret_parameter secret = decode_hash(arg);
    bool compressed_flag = true;
    if (secret == null_hash)
    {
        secret = libwallet::wif_to_secret(arg);
        compressed_flag = libwallet::is_wif_compressed(arg);
    }
    // Overrides for compression
    if (is_compressed == 0)
        compressed_flag = false;
    else if (is_compressed == 1)
        compressed_flag = true;
    if (secret == null_hash || !key.set_secret(secret, compressed_flag))
        return false;
    return true;
}
bool read_private_key(elliptic_curve_key& key, int is_compressed=-1)
{
    if (!read_private_key(key, read_stdin(), is_compressed))
    {
        std::cerr << "Invalid private key." << std::endl;
        return false;
    }
    return true;
}

bool read_public_or_private_key(elliptic_curve_key& key)
{
    std::string arg = read_stdin();
    if (read_private_key(key, arg))
        return true;
    data_chunk pubkey = decode_hex(arg);
    if (key.set_public_key(pubkey))
        return true;
    std::cerr << "Invalid public or private key." << std::endl;
    return false;
}

// Used by hd-priv and hd-pub commands.
bool read_hd_command_args(int argc, char** argv,
    bool& is_hard, uint32_t& index)
{
    if (argc == 1 || argc > 3)
    {
        std::cerr << "Usage: sx hd-priv [--hard] INDEX" << std::endl;
        return false;
    }
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--hard")
        {
            is_hard = true;
            continue;
        }
        try
        {
            index = boost::lexical_cast<uint32_t>(arg);
        }
        catch (const boost::bad_lexical_cast&)
        {
            std::cerr << "hd-priv: Bad INDEX provided." << std::endl;
            return false;
        }
    }
    return true;
}

ec_secret generate_random_secret()
{
    std::random_device random;
    std::default_random_engine engine(random());
    ec_secret secret;
    for (uint8_t& byte: secret)
        byte = engine() % std::numeric_limits<uint8_t>::max();
    return secret;
}

#endif

