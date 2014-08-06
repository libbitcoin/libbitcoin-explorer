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
#ifndef BYTE_HPP
#define BYTE_HPP

#include <iostream>
#include <stdint.h>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper for numeric byte, because byte-sized integral types 
 * stream as characters.
 */
class byte
{
public:

    /**
     * Constructor.
     */
    byte() 
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  number  The value to initialize with.
     */
    byte(const std::string& number)
    {
        std::stringstream(number) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    byte(const uint8_t& value)
        : value_(value) {}

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    byte(const byte& other)
        : byte(other.value_) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    uint8_t& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const uint8_t&() const
    {
        return value_;
    }

    /**
     * Overload stream in. If input is not a number sets 0x00 in argument.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, byte& argument)
    {
        int number;
        input >> number;

        argument.value_ = static_cast<uint8_t>(number);
        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, const byte& argument)
    {
        output << static_cast<int>(argument.value_);
        return output;
    }

    /**
     * Overload prefix increment.
     *
     * @return  This object referenced, with incremented value.
     */
    byte& operator++()
    {
        ++value_;
        return *this;
    }

    /**
     * Overload postfix increment.
     *
     * @return  This object copied, with incremented value.
     */
    byte operator++(int)
    {
        byte temp(*this);
        operator++();
        return temp;
    }

private:

    /**
     * The state of this object.
     */
    uint8_t value_;
};

} // sx
} // serializer

#endif