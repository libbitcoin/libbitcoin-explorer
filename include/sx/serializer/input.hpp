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
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/point.hpp>
#include <sx/serializer/script.hpp>
#include <sx/utility/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Parse two-three tokens into an output point.
 * Throws if the hash digest or index is not valid.
 * 
 * @param[out] input   The out point to populate.
 * @param[in]  tokens  The two-three tokens to parse.
 */
static void parse_input(bc::transaction_input_type& input,
    const std::vector<std::string>& tokens)
{
    input.script = bc::script_type();
    input.sequence = bc::max_sequence;
    input.previous_output = point(tokens[0] + ":" + tokens[1]);
    if (tokens.size() == 3)
        deserialize(input.sequence, tokens[2]);
}

static pt::ptree property_tree(const bc::transaction_input_type& tx_input);

/**
 * Serialization helper stub for transaction_input_type.
 */
class input
{
public:

    /**
     * Constructor.
     */
    input()
        : value_()
    {
    }
    
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
     * Initialization constructor. Only the point is retained.
     * 
     * @param[in]  value  The value to initialize with.
     */
    input(const bc::transaction_input_type& value)
        : value_(value)
    {
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
     * Initialization constructor. Aspects of the input other than the point
     * are defaulted.
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
     * Overload cast to property tree.
     *
     * @return  This object's value cast to a property tree.
     */
    operator const pt::ptree() const
    {
        return property_tree(value_);
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& stream, input& argument)
    {
        std::string tuple;
        stream >> tuple;

        std::vector<std::string> tokens;
        split(tuple, tokens, SX_TX_POINT_DELIMITER);
        if (tokens.size() != 2 && tokens.size() != 3)
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
        const auto& out = argument.value_;
        output << point(out.previous_output) << SX_TX_POINT_DELIMITER 
            << out.sequence;
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::transaction_input_type value_;
};

/**
 * Generate a property tree for a transaction input.
 *
 * @param[in]  tx_input  The input.
 * @return               A property tree of input.
 */
static pt::ptree property_tree(const bc::transaction_input_type& tx_input)
{
    pt::ptree tree;
    tree.put("input.previous_output", point(tx_input.previous_output));
    tree.put("input.script", script(tx_input.script).mnemonic());
    tree.put("input.sequence", tx_input.sequence);

    bc::payment_address script_address;
    if (extract(script_address, tx_input.script))
        tree.put("input.address", address(script_address));

    return tree;
}

/**
 * Generate a property tree for a set of transaction inputs.
 *
 * @param[in]  tx_inputs  The set of transaction inputs.
 * @return                A property tree of inputs.
 */
static pt::ptree property_tree(
    const std::vector<bc::transaction_input_type>& tx_inputs)
{
    pt::ptree tree;
    for (const auto& tx_input: tx_inputs)
        tree.add_child("inputs", property_tree(tx_input));

    return tree;
}

/**
 * Generate a property tree for an input.
 *
 * @param[in]  input  The input.
 * @return            A property tree of input.
 */
static pt::ptree property_tree(const input& input)
{
    const bc::transaction_input_type& tx_input = input;

    pt::ptree tree;
    tree = property_tree(tx_input);
    return tree;
}

/**
 * Generate a property tree for a set of inputs.
 *
 * @param[in]  inputs  The set of inputs.
 * @return             A property tree of inputs.
 */
static pt::ptree property_tree(const std::vector<input>& inputs)
{
    pt::ptree tree;
    for (const auto& input: inputs)
        tree.add_child("inputs", property_tree(
            (const bc::transaction_input_type&)input));

    return tree;
}

} // sx
} // serializer

#endif