#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"
using namespace bc;

void show_tx(const transaction_type& tx)
{
    std::cout << "hash: " << hash_transaction(tx) << std::endl;
    std::cout << "version: " << tx.version <<std::endl;
    std::cout << "locktime: " << tx.locktime << std::endl;
    for (const transaction_input_type& input: tx.inputs)
    {
        std::cout << "Input:" << std::endl;
        std::cout << "  previous output: "
            << input.previous_output.hash << ":"
            << input.previous_output.index << std::endl;
        std::cout << "  script: " << pretty(input.script) << std::endl;
        std::cout << "  sequence: " << input.sequence << std::endl;
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
}

void json_show_tx(const transaction_type& tx)
{
    std::cout << "{" << std::endl;
    std::cout << "  \"hash\": \"" << hash_transaction(tx)
        << "\"," << std::endl;
    std::cout << "  \"version\": " << tx.version << "," << std::endl;
    std::cout << "  \"locktime\": " << tx.locktime << "," << std::endl;
    std::cout << "  \"inputs\": [" << std::endl;
    bool is_first = true;
    for (const transaction_input_type& input: tx.inputs)
    {
        if (is_first)
            is_first = false;
        else
            std::cout << "," << std::endl;
        std::cout << "   {\"previous_output\": \""
            << input.previous_output.hash << ":"
            << input.previous_output.index << "\"," << std::endl;
        std::cout << "    \"script\": \"" << pretty(input.script)
            << "\"," << std::endl;
        std::cout << "    \"sequence\": " << input.sequence
            << "," << std::endl;
        std::cout << "    \"address\": ";
        payment_address addr;
        if (extract(addr, input.script))
            std::cout << "\"" << addr.encoded() << "\"";
        else
            std::cout << "null";
        std::cout << "}";
    }
    std::cout << std::endl << "  ]," << std::endl;
    std::cout << "  \"outputs\": [" << std::endl;
    is_first = true;
    for (const transaction_output_type& output: tx.outputs)
    {
        if (is_first)
            is_first = false;
        else
            std::cout << "," << std::endl;
        std::cout << "   {\"value\": " << output.value << "," << std::endl;
        std::cout << "    \"script\": \"" << pretty(output.script)
            << "\"," << std::endl;
        std::cout << "    \"address\": ";
        payment_address addr;
        if (extract(addr, output.script))
            std::cout << "\"" << addr.encoded() << "\"";
        else
            std::cout << "null";
        std::cout << "}";
    }
    std::cout << std::endl << "  ]" << std::endl;
    std::cout << "}" << std::endl;
}

int main(int argc, char** argv)
{
    std::string filename = "-";
    bool json_output = false;
    for (size_t i = 1; i < argc; ++i)
    {
        const std::string arg = argv[i];
        if (arg == "-j" || arg == "--json")
        {
            json_output = true;
            continue;
        }
        if (filename != "-")
        {
            std::cerr << "Usage: sx showtx [-j] FILENAME" << std::endl;
            return -1;
        }
        filename = arg;
    }
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
    if (json_output)
        json_show_tx(tx);
    else
        show_tx(tx);
    return 0;
}

