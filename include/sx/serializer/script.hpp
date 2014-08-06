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
#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hex.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

    static void operation_from_data(bc::operation& op, 
        const bc::data_chunk& data)
    {
        constexpr size_t max_special = 75;

        if (data.size() <= max_special)
            op.code = bc::opcode::special;
        else if (data.size() < std::numeric_limits<uint8_t>::max())
            op.code = bc::opcode::pushdata1;
        else if (data.size() < std::numeric_limits<uint16_t>::max())
            op.code = bc::opcode::pushdata2;
        else if (data.size() < std::numeric_limits<uint32_t>::max())
            op.code = bc::opcode::pushdata4;
        else
            op.code = bc::opcode::bad_operation;

        if (op.code != bc::opcode::bad_operation)
            op.data = data;
    }

    // This should be sxs with bc::pretty()
    static bool script_from_tokens(bc::script_type& script,
        const std::vector<std::string>& tokens)
    {
        for (auto& token = tokens.begin(); token != tokens.end(); token++)
        {
            bc::operation op;

            if (*token == "[")
            {
                std::string encoded;
                while (++token != tokens.end() && *token != "]")
                    encoded += *token;

                if (*token != "]")
                    return false;

                operation_from_data(op, bc::decode_hex(encoded));
            }
            else
                op.code = bc::string_to_opcode(*token);

            script.push_operation(op);
        }

        return true;
    }

/**
 * Serialization helper to convert between hex/raw script and script_type.
 */
    class script
{
public:

    /**
     * Constructor.
     */
    script()
        : value_()
    {
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    script(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    script(const bc::script_type& value)
        : value_(value)
    {
    }

    /**
     * Initialization constructor.
     * We handle pretty printing internal to the script serializer because
     * we do not use boost program_options to read the words as a single
     * argument. Instead we read a set of string arguments and then explicitly
     * load them here.
     * 
     * @param[in]  tokens  The value to initialize with.
     */
    script(const std::vector<std::string>& tokens)
    {
        if (!script_from_tokens(value_, tokens))
        {
            std::string sentence;
            join(tokens, sentence);
            throw po::invalid_option_value(sentence);
        }
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    script(const script& other)
        : script(other.value_)
    {
    }

    /**
    * Return a reference to the data member.
    *
    * @return  A reference to the object's internal data.
    */
    bc::script_type& data()
    {
        return value_;
    }

    /**
     * Return a pretty-printed copy of the script.
     * See comments on the tokens constructor. We expose this method here for 
     * symmetry with the construction approach.
     *
     * @return  A pretty-printed copy of the internal script.
     */
    const std::string pretty() const
    {
        return bc::pretty(value_);
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::script_type&() const
    {
        return value_; 
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, script& argument)
    {
        std::string hexadecimal;
        input >> hexadecimal;

        try
        {
            argument.value_ = bc::parse_script(hex(hexadecimal));
        }
        catch (bc::end_of_stream)
        {
            throw po::invalid_option_value(hexadecimal);
        }

        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const script& argument)
    {
        output << hex(bc::save_script(argument.value_));
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::script_type value_;
};

} // sx
} // serializer

#endif