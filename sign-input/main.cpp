#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>

using namespace bc;

void load_tx(transaction_type& tx, const std::string& filename)
{
    std::ifstream infile(filename, std::ifstream::binary);
    // Get size of file.
    infile.seekg(0, infile.end);
    long size = infile.tellg();
    infile.seekg(0);
    // Allocate memory for file contents.
    data_chunk raw_tx(size);
    char* buffer = reinterpret_cast<char*>(raw_tx.data());
    infile.read(buffer, size);
    infile.close();
    // Deserialize tx.
    satoshi_load(raw_tx.begin(), raw_tx.end(), tx);
}

std::string dump_file(std::istream& in_file)
{
    std::istreambuf_iterator<char> it(in_file);
    std::istreambuf_iterator<char> end;
    return std::string(it, end);
}

private_data read_private_key_data()
{
    std::string raw_private_key;
    raw_private_key = dump_file(std::cin);
    return private_data(raw_private_key.begin(), raw_private_key.end());
}

// Passing in signing_key pointer by reference.
bool load_private_key(elliptic_curve_key& signing_key)
{
    if (!signing_key.set_private_key(read_private_key_data()))
    {
        std::cerr << "sign-input: Error loading private key" << std::endl;
        return false;
    }
    return true;
}

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
        std::cerr << "sign-input: Error generating signature hash" << std::endl;
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
    const std::string tx_filename = argv[1];
    transaction_type tx;
    load_tx(tx, tx_filename);
    const std::string index_str = argv[2];
    size_t input_index;
    try
    {
        input_index = boost::lexical_cast<size_t>(index_str);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "sign-input: Bad N provided" << std::endl;
        return -1;
    }
    if (input_index >= tx.inputs.size())
    {
        std::cerr << "sign-input: N out of range" << std::endl;
        return -1;
    }
    elliptic_curve_key signing_key;
    if (!load_private_key(signing_key))
        return -1;
    if (!sign(tx, input_index, signing_key))
        return -1;
    // Now re-serialize transaction.
    data_chunk raw_tx(satoshi_raw_size(tx));
    satoshi_save(tx, raw_tx.begin());
    std::ofstream outfile(tx_filename, std::ofstream::binary);
    const char* buffer = reinterpret_cast<const char*>(raw_tx.data());
    outfile.write(buffer, raw_tx.size());
    return 0;
}

