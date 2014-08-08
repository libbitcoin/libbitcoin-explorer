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
#ifndef RAW_HPP
#define RAW_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between a byte stream and data_chunk.
 */
class raw
{
public:

    /**
     * Constructor.
     */
    raw()
        : value_()
    {
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    raw(const bc::data_chunk& value)
        : value_(value)
    {
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    raw(const raw& other)
        : raw(other.value_)
    {
    }

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::data_chunk& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::data_chunk&() const
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
    friend std::istream& operator>>(std::istream& input, raw& argument)
    {
        std::istreambuf_iterator<char> first(input), last;
        argument.value_.assign(first, last);
        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, const raw& argument)
    {
        std::ostreambuf_iterator<char> iterator(output);
        std::copy(argument.value_.begin(), argument.value_.end(), iterator);
        return output;
    }

private:

    /**
     * The state of this object's file data.
     */
    bc::data_chunk value_;
};

} // sx
} // serializer

#endif