#include <bitcoin/bitcoin.hpp>
using namespace bc;

operation create_data_operation(data_chunk& data)
{
    BITCOIN_ASSERT(data.size() < std::numeric_limits<uint32_t>::max());
    operation op;
    op.data = data;
    if (data.size() <= 75)
        op.code = opcode::special;
    else if (data.size() < std::numeric_limits<uint8_t>::max())
        op.code = opcode::pushdata1;
    else if (data.size() < std::numeric_limits<uint16_t>::max())
        op.code = opcode::pushdata2;
    else if (data.size() < std::numeric_limits<uint32_t>::max())
        op.code = opcode::pushdata4;
    return op;
}

script_type script_from_pretty(const std::string& pretty_script)
{
    script_type script_object;
    std::stringstream splitter;
    splitter << pretty_script;
    std::string token;
    while (splitter >> token)
    {
        operation op;
        if (token == "[")
        {
            std::string encoded_hex;
            while ((splitter >> token) && token != "]")
                encoded_hex += token;
            data_chunk data = decode_hex(encoded_hex);
            if (token != "]")
            {
                log_warning() << "Premature end of script.";
                return script_type();
            }
            op = create_data_operation(data);
        }
        else
        {
            op.code = string_to_opcode(token);
        }
        script_object.push_operation(op);
    }
    return script_object;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: sx rawscript [ARGS]..." << std::endl;
        return -1;
    }
    std::string joined_args;
    for (size_t i = 1; i < argc; ++i)
        joined_args += std::string(argv[i]) + " ";
    script_type parsed_script = script_from_pretty(joined_args);
    std::cout << save_script(parsed_script) << std::endl;
    return 0;
}

