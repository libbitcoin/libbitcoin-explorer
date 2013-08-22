#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

bool sign(transaction_type& tx, size_t input_index,
    const elliptic_curve_key& key, const script_type& script_code)
{
    transaction_input_type& input = tx.inputs[input_index];

    const data_chunk public_key = key.public_key();
    if (public_key.empty())
    {
        std::cerr << "sign-input: Internal error getting public key."
            << std::endl;
        return false;
    }
    hash_digest tx_hash =
        script_type::generate_signature_hash(tx, input_index, script_code, 1);
    if (tx_hash == null_hash)
    {
        std::cerr << "sign-input: Error generating signature hash."
            << std::endl;
        return false;
    }
    data_chunk signature = key.sign(tx_hash);
    signature.push_back(0x01);
    std::cout << signature << std::endl;
    return true;
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: sign-input FILENAME N SCRIPT_CODE" << std::endl;
        return -1;
    }
    const std::string filename = argv[1];
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
    const std::string index_str = argv[2];
    size_t input_index;
    try
    {
        input_index = boost::lexical_cast<size_t>(index_str);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "sign-input: Bad N provided." << std::endl;
        return -1;
    }
    const script_type script_code = parse_script(decode_hex(argv[3]));
    if (input_index >= tx.inputs.size())
    {
        std::cerr << "sign-input: N out of range." << std::endl;
        return -1;
    }
    elliptic_curve_key signing_key;
    if (!read_private_key(signing_key))
        return -1;
    if (!sign(tx, input_index, signing_key, script_code))
        return -1;
    return 0;
}

