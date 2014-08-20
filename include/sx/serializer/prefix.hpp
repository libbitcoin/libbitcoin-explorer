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
#ifndef PREFIX_HPP
#define PREFIX_HPP

#include <iostream>
#include <string>
#include <cstdint>
#include <sx/define.hpp>
#include <sx/utility/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between binary string and bitset.
 */
class prefix
{
public:

    /**
     * Default constructor.
     */
    prefix();

    /**
     * Initialization constructor.
     * @param[in]  bin  The value to initialize with.
     */
    prefix(const std::string& binary);

    /**
     * @param[in]  value  The value to initialize with.
     */
    prefix(const bitset& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    prefix(const prefix& other);

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const bitset&() const;

    ///**
    // * Overload cast to unsigned 32 bit value.
    // * @return  This object's value cast to 32 bit value.
    // */
    //operator const uint32_t() const;

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, prefix& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const prefix& argument);

private:

    /**
     * The state of this object.
     */
    bitset value_;
};

} // sx
} // serializer

#endif