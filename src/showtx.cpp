#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"
using namespace bc;

int main(int argc, char** argv)
{
    std::string filename = "-";
    if (argc == 2)
        filename = argv[1];
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
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
        std::cout << "  script: " << pretty(input.script)
            << "  sequence: " << input.sequence << std::endl;
        payment_address addr;
        if (extract(addr, input.script))
            std::cout << "  address: " << addr.encoded() << std::endl;
    }
    for (const transaction_output_type& output: tx.outputs)
    {
        std::cout << "Output:" << std::endl;
        std::cout << "  value: " << output.value << std::endl;
        std::cout << "  script: " << pretty(output.script) << std::endl;
        payment_address addr;
        if (extract(addr, output.script))
            std::cout << "  address: " << addr.encoded() << std::endl;
    }
    return 0;
}

