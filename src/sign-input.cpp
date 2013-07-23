#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

// Passing in signing_key pointer by reference.
script build_output_script(const short_hash& public_key_hash)
{
    script result;
    result.push_operation({opcode::dup, data_chunk()});
    result.push_operation({opcode::hash160, data_chunk()});
    result.push_operation({opcode::special,
        data_chunk(public_key_hash.begin(), public_key_hash.end())});
    result.push_operation({opcode::equalverify, data_chunk()});
    result.push_operation({opcode::checksig, data_chunk()});
    return result;
}

bool sign(transaction_type& tx, size_t input_index,
    const elliptic_curve_key& key)
{
    transaction_input_type& input = tx.inputs[input_index];

    const data_chunk public_key = key.public_key();
    if (public_key.empty())
    {
        std::cerr << "sign-input: Internal error getting public key."
            << std::endl;
        return false;
    }
    script script_code = 
        build_output_script(generate_ripemd_hash(public_key));

    hash_digest tx_hash =
        script::generate_signature_hash(tx, input_index, script_code, 1);
    if (tx_hash == null_hash)
    {
        std::cerr << "sign-input: Error generating signature hash."
            << std::endl;
        return false;
    }
    data_chunk signature = key.sign(tx_hash);
    signature.push_back(0x01);

    script& input_script = input.input_script;
    input_script = script();
    input_script.push_operation({opcode::special, signature});
    input_script.push_operation({opcode::special, public_key});
    return true;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: sign-input FILENAME N" << std::endl;
        return -1;
    }
    const std::string filename = argv[1];
    transaction_type tx;
    load_tx(tx, filename);
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
    if (input_index >= tx.inputs.size())
    {
        std::cerr << "sign-input: N out of range." << std::endl;
        return -1;
    }
    elliptic_curve_key signing_key;
    if (!read_private_key(signing_key))
        return -1;
    if (!sign(tx, input_index, signing_key))
        return -1;
    // Now re-serialize transaction.
    data_chunk raw_tx(satoshi_raw_size(tx));
    satoshi_save(tx, raw_tx.begin());
    if (filename == "-")
        std::cout << raw_tx << std::endl;
    else
    {
        std::ofstream outfile(filename, std::ofstream::binary);
        outfile << raw_tx;
    }
    return 0;
}

