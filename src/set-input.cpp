#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: set-input FILENAME N" << std::endl;
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
        std::cerr << "set-input: Bad N provided." << std::endl;
        return -1;
    }
    if (input_index >= tx.inputs.size())
    {
        std::cerr << "set-input: N out of range." << std::endl;
        return -1;
    }
    // Read script from STDIN.
    std::string hex_script = read_stdin();
    script_type new_input_script = parse_script(decode_hex(hex_script));
    // Set input.
    tx.inputs[input_index].script = new_input_script;
    // Now re-serialize transaction.
    data_chunk raw_tx(satoshi_raw_size(tx));
    satoshi_save(tx, raw_tx.begin());
    std::cout << raw_tx << std::endl;
    return 0;
}

