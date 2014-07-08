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
#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <bitcoin/bitcoin.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

#define SX_SERIALIZER_POINT_PREFIX_EXCEPTION \
    "Elliptic curve point must start with 0x02 or 0x03."

#define SX_SERIALIZER_POINT_SIZE_EXCEPTION \
    "Elliptic curve point must be 33 bytes."

/**
 * Serialization helper to convert between hex string and ec_point.
 */
class point
{
public:

    /**
     * Constructor.
     */
    point()
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    point(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    point(const point& other)
        : value_(other.value_) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::ec_point& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::ec_point() const
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
    friend std::istream& operator>>(std::istream& input, point& argument)
    {
        std::string hex;
        input >> hex;
        auto chunk = bc::decode_hex(hex);

        // TODO: determine how to properly raise error in deserialization.
        if (chunk.size() != bc::ec_compressed_size)
            throw std::exception(SX_SERIALIZER_POINT_SIZE_EXCEPTION);

        // TODO: determine how to properly raise error in deserialization.
        if (chunk[0] != 0x02 && chunk[0] != 0x03)
            throw std::exception(SX_SERIALIZER_POINT_PREFIX_EXCEPTION);
        
        argument.value_.assign(chunk.begin(), chunk.end());
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
        const point& argument)
    {
        output << bc::encode_hex(argument.value_);
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::ec_point value_;
};

} // sx
} // serializer

#endif