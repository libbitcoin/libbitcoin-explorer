#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>

using namespace bc;

// Currently unused.
bool display_help()
{
    puts("Usage: mktx FILENAME [ARGS]...");
    puts("");
    puts("Options:");
    puts("");
    puts(" -i, --input\tPrevious output in the form TXHASH:INDEX");
    puts(" -o, --output\tSpecify a destination ADDRESS:AMOUNT");
    puts("\t\tAMOUNT uses internal bitcoin values");
    puts("\t\t  0.1 BTC = 0.1 * 10^8 = 1000000");
    puts("");
    puts("Please email suggestions and questions to <genjix@riseup.net>.");
    return -1;
}

bool two_args_remain(size_t current_arg, int argc)
{
    return argc - current_arg >= 2;
}

bool load_outpoint(output_point& prevout, const std::string& parameter)
{
    std::vector<std::string> strs;
    boost::split(strs, parameter, boost::is_any_of(":"));
    if (strs.size() != 2)
    {
        std::cerr << "mktx: Format for output point is TXHASH:INDEX."
            << std::endl;
        return false;
    }
    const std::string& hex_string = strs[0];
    if (hex_string.size() != 64)
    {
        std::cerr << "mktx: Incorrect TXHASH." << std::endl;
        return false;
    }
    prevout.hash = decode_hex_digest<hash_digest>(hex_string);
    const std::string& index_string = strs[1];
    try
    {
        prevout.index = boost::lexical_cast<uint32_t>(index_string);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "mktx: Bad INDEX provided." << std::endl;
        return false;
    }
    return true;
}

bool add_input(transaction_type& tx, const std::string& parameter)
{
    transaction_input_type input;
    output_point& prevout = input.previous_output;
    if (!load_outpoint(prevout, parameter))
        return false;
    input.sequence = 4294967295;
    tx.inputs.push_back(input);
    std::cerr << "Added input "
        << prevout.hash << ":" << prevout.index << std::endl;
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

bool add_output(transaction_type& tx, const std::string& parameter)
{
    transaction_output_type output;
    std::vector<std::string> strs;
    boost::split(strs, parameter, boost::is_any_of(":"));
    if (strs.size() != 2)
    {
        std::cerr << "mktx: Format for output is ADDRESS:VALUE."
            << std::endl;
        return false;
    }
    const std::string& addr_str = strs[0];
    payment_address addr;
    if (!addr.set_encoded(addr_str))
    {
        std::cerr << "mktx: Bad address '" << addr_str << "'." << std::endl;
        return false;
    }
    const std::string& value_str = strs[1];
    try
    {
        output.value = boost::lexical_cast<uint64_t>(value_str);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "mktx: Bad VALUE provided." << std::endl;
        return false;
    }
    output.output_script = build_output_script(addr.hash());
    tx.outputs.push_back(output);
    std::cerr << "Added output sending " << output.value << " Satoshis to "
        << addr.encoded() << "." << std::endl;
    return true;
}

bool modify(transaction_type& tx,
    const std::string& action, const std::string& parameter)
{
    if (action == "-i" || action == "--input")
        return add_input(tx, parameter);
    else if (action == "-o" || action == "--output")
        return add_output(tx, parameter);
    std::cerr << "mktx: Action '" << action << "' doesn't exist." << std::endl;
    return false;
}

int main(int argc, char** argv)
{
    if (argc < 2)
        return display_help();
    const std::string filename = argv[1];
    // Now create transaction.
    transaction_type tx;
    tx.version = 1;
    tx.locktime = 0;
    size_t current_arg = 2;
    while (two_args_remain(current_arg, argc) && current_arg != argc)
    {
        const std::string action = argv[current_arg],
            parameter = argv[current_arg + 1];
        if (!modify(tx, action, parameter))
            return -1;
        current_arg += 2;
        BITCOIN_ASSERT(current_arg <= argc);
    }
    // Now serialize transaction.
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

