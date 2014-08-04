/**
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
#include <sx/command/rawscript.hpp>

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static void operation_from_data(operation& op, const data_chunk& data)
{
    constexpr size_t max_special = 75;

    if (data.size() <= max_special)
        op.code = opcode::special;
    else if (data.size() < std::numeric_limits<uint8_t>::max())
        op.code = opcode::pushdata1;
    else if (data.size() < std::numeric_limits<uint16_t>::max())
        op.code = opcode::pushdata2;
    else if (data.size() < std::numeric_limits<uint32_t>::max())
        op.code = opcode::pushdata4;
    else 
        op.code = opcode::bad_operation;

    if (op.code != opcode::bad_operation)
        op.data = data;
}

static bool script_from_tokens(script_type& script, 
    const std::vector<std::string>& tokens)
{
    for (auto& token = tokens.begin(); token != tokens.end(); token++)
    {
        operation op;

        if (*token == "[")
        {
            std::string encoded;
            while (++token != tokens.end() && *token != "]")
                encoded += *token;

            if (*token != "]")
                return false;

            operation_from_data(op, decode_hex(encoded));
        }
        else
        {
            op.code = string_to_opcode(*token);
        }

        script.push_operation(op);
    }

    return true;
}

console_result rawscript::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const auto& tokens = get_tokens_argument();

    // TODO: create script serializer and bury this.
    script_type script;
    if (!script_from_tokens(script, tokens))
    {
        cerr << SX_RAWSCRIPT_INVALID << std::endl;
        return console_result::okay;
    }

    output << hex(save_script(script)) << std::endl;
    return console_result::okay;
}

