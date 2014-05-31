/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
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

bool invoke(const int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: sx rawscript [ARGS]..." << std::endl;
        return -1;
    }
    std::string joined_args;
    for (int i = 1; i < argc; ++i)
        joined_args += std::string(argv[i]) + " ";
    script_type parsed_script = script_from_pretty(joined_args);
    std::cout << save_script(parsed_script) << std::endl;
    return 0;
}

