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
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hex.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

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
     * @param[in]  hexcode  The value to initialize with.
     */
    script(const std::string& hexcode)
    {
        std::stringstream(hexcode) >> *this;
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
     * @param[in]  mnemonics  The mnemonic tokens to initialize with.
     */
    script(const std::vector<std::string>& mnemonics)
    {
        std::string script;
        join(mnemonics, script);

        value_ = bc::unpretty(script);
        if (value_.operations().empty())
            throw po::invalid_option_value(script);
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
     * @return  A mnemonic-printed copy of the internal script.
     */
    const std::string mnemonic() const
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
        std::string hexcode;
        input >> hexcode;

        try
        {
            argument.value_ = bc::parse_script(hex(hexcode));
        }
        catch (bc::end_of_stream)
        {
            throw po::invalid_option_value(hexcode);
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