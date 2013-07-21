#include <iostream>
#include <bitcoin/bitcoin.hpp>
using namespace bc;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: showtx FILENAME" << std::endl;
        return -1;
    }
    const std::string& filename = argv[1];
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
    transaction_type tx;
    satoshi_load(raw_tx.begin(), raw_tx.end(), tx);
    // Show details.
    std::cout << "hash: " << hash_transaction(tx) << std::endl;
    std::cout << "version: " << tx.version
        << "  locktime: " << tx.locktime << std::endl;
    for (const transaction_input_type& input: tx.inputs)
    {
        std::cout << "Input:" << std::endl;
        std::cout << "  previous output: "
            << input.previous_output.hash << ":"
            << input.previous_output.index << std::endl;
        std::cout << "  script: " << pretty(input.input_script)
            << "  sequence: " << input.sequence << std::endl;
        payment_address addr;
        if (extract_input_address(addr, input.input_script))
            std::cout << "  address: " << addr.encoded() << std::endl;
    }
    for (const transaction_output_type& output: tx.outputs)
    {
        std::cout << "Output:" << std::endl;
        std::cout << "  value: " << output.value << std::endl;
        std::cout << "  script: " << pretty(output.output_script) << std::endl;
        payment_address addr;
        if (extract(addr, output.output_script))
            std::cout << "  address: " << addr.encoded() << std::endl;
    }
    return 0;
}

