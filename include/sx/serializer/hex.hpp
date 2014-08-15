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
#ifndef HEX_HPP
#define HEX_HPP

#include <array>
#include <iostream>
#include <string>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between hex string and data_chunk.
 */
class hex
{
public:

    /**
     * Default constructor.
     */
    hex();

    /**
     * Initialization constructor.
     * @param[in]  hex  The value to initialize with.
     */
    hex(const std::string& hexcode);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    hex(const bc::data_chunk& value);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    template<size_t Size>
    hex(const bc::byte_array<Size>& value)
        : value_(value.begin(), value.end())
    {
    }

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    hex(const hex& other);

    /**
     * Return a reference to the data member.
     * @return  A reference to the object's internal data.
     */
    bc::data_chunk& data();

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const bc::data_chunk&() const;

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, hex& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, const hex& argument);

private:

    /**
     * The state of this object.
     */
    bc::data_chunk value_;
};

} // sx
} // serializer

#endif