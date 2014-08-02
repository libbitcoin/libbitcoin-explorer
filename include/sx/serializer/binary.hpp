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
#ifndef BINARY_HPP
#define BINARY_HPP

#include <array>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

typedef boost::dynamic_bitset<uint8_t> bitset;

/**
 * Serialization helper to convert between binary string and data_chunk.
 */
class binary
{
public:

    /**
     * Constructor.
     */
    binary() 
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  bin  The value to initialize with.
     */
    binary(const std::string& bin)
    {
        std::stringstream(bin) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    binary(const bitset& value)
        : value_(value) {}

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    binary(const binary& other)
        : binary(other.value_) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bitset& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bitset&() const
    {
        return value_; 
    }

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, binary& argument)
    {
        std::string bin;
        input >> bin;
       
        bitset value(bin);
        if (bin.length() != value.size())
            throw po::invalid_option_value(bin);

        argument.value_.swap(value);
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
        const binary& argument)
    {
        std::string bin;
        boost::to_string(argument.value_, bin);

        output << bin;
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bitset value_;
};

} // sx
} // serializer

#endif