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
#ifndef SIGHASH_HPP
#define SIGHASH_HPP

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between text and sighash.
 */
class signature_hash
{
public:

    /**
     * Default constructor, sets sighash::single.
     */
    signature_hash();

    /**
     * Initialization constructor.
     * @param[in]  token  The value to initialize with.
     */
    signature_hash(const std::string& token);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    signature_hash(const bc::sighash& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    signature_hash(const signature_hash& other);

    /**
     * Return a reference to the data member.
     * @return  A reference to the object's internal data.
     */
    operator const bc::sighash() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, 
        signature_hash& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const signature_hash& argument);

private:

    /**
     * The state of this object's sighash engine data.
     */
    bc::sighash value_;
};

} // sx
} // serializer

#endif