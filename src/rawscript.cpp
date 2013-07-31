#include <bitcoin/bitcoin.hpp>
using namespace bc;

script script_from_pretty(const std::string& pretty_script)
{
    script script_object;
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
            op.data = decode_hex(encoded_hex);
            if (token != "]")
            {
                log_warning() << "Premature end of script.";
                return script();
            }
            op.code = opcode::special;
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
    script parsed_script = script_from_pretty(joined_args);
    std::cout << save_script(parsed_script) << std::endl;
    return 0;
}

