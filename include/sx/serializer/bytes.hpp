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
#ifndef BYTES_HPP
#define BYTES_HPP

#include <array>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <bitcoin/bitcoin.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between hex string and data_chunk.
 */
class bytes
{
public:

    /**
     * Constructor.
     */
    bytes() 
        : value() {}

    /**
     * Initialization counstructor.
     * 
     * @param[in]  array  The value to initialize with.
     */
    template<size_t Size>
    bytes(const bc::byte_array<Size>& array)
        : value(array.begin(), array.end()) {}

    /**
     * Initialization counstructor.
     * 
     * @param[in]  chunk  The value to initialize with.
     */
    bytes(const bc::data_chunk& chunk)
        : value(chunk) {}

    /**
     * Initialization counstructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    bytes(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Copy counstructor.
     *
     * @param[in]  argument  The object to copy into self on construct.
     */
    bytes(const bytes& argument)
        : value(argument.value) {}

    /**
     * Overload cast to bc::data_chunk.
     *
     * @return  This object's value cast to bc::data_chunk.
     */
    operator bc::data_chunk() const
    {
        return value; 
    }

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, bytes& argument)
    {
        std::string hex;
        input >> hex;
        argument.value = bc::decode_hex(hex);
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
        const bytes& argument)
    {
        output << bc::encode_hex(argument.value);
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::data_chunk value;
};

} // sx
} // serializer

#endif