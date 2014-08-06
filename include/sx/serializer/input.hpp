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
#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/btc256.hpp>
#include <sx/utility/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {
    
    /**
     * Parse tokens into the transaction input.
     * Throws if the hash digest or index is not valid.
     *
     * @param[out] input   The transaction input to populate.
     * @param[in]  tokens  The pre-validated two tokens to parse.
     */
    static void parse_input(bc::transaction_input_type& input,
        const std::vector<std::string>& tokens)
    {
        // validate and deserialize the transaction hash
        const btc256 digest(tokens[0]);
        const bc::hash_digest& txhash = digest;

        // copy the input point values
        auto& point = input.previous_output;
        std::copy(txhash.begin(), txhash.end(), point.hash.begin());
        deserialize(point.index, tokens[1]);

        // initialize the input
        input.sequence = bc::max_sequence;
        input.script = bc::script_type();
    }

/**
 * Serialization helper to convert between a base58-string:number 
 * and transaction_input_type.
 */
class input
{
public:

    /**
     * Constructor.
     */
    input()
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  tuple  The value to initialize with.
     */
    input(const std::string& tuple)
    {
        std::stringstream(tuple) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    input(const bc::transaction_input_type& value)
        : value_(value)
    {
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    input(const bc::input_point& value)
    {
        value_.previous_output = value;
        value_.sequence = bc::max_sequence;
        value_.script = bc::script_type();
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    input(const input& other)
        : input(other.value_)
    {
    }

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::transaction_input_type& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::transaction_input_type&() const
    {
        return value_; 
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   stream    The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& stream, input& argument)
    {
        std::string tuple;
        stream >> tuple;

        std::vector<std::string> tokens;
        split(tuple, tokens, SX_TX_POINT_DELIMITER);
        if (tokens.size() != 2)
            throw po::invalid_option_value(tuple);

        parse_input(argument.value_, tokens);
        return stream;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, 
        const input& argument)
    {
        // see bc::concat_point()
        const auto& out = argument.value_.previous_output;
        output << btc256(out.hash) << SX_TX_POINT_DELIMITER << out.index;
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::transaction_input_type value_;
};

} // sx
} // serializer

#endif