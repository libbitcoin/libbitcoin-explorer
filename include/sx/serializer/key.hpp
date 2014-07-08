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
#ifndef KEY_HPP
#define KEY_HPP

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/coin.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

#define SX_SERIALIZER_KEY_EXCEPTION \
    "Invalid public or private key."

/**
 * Serialization helper to convert between hex string and elliptic_curve_key.
 * Reads public or private key and writes corresponding public key.
 */
class key
{
public:

    /**
     * Constructor.
     */
    key()
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    key(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    key(const key& other)
        : value_(other.value_) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::elliptic_curve_key& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::elliptic_curve_key() const
    {
        return value_; 
    }

    /**
     * Overload cast to bc::data_chunk, returning the public key value.
     *
     * @return  This object's value cast to bc::data_chunk.
     */
    operator const bc::data_chunk() const
    {
        return value_.public_key(); 
    }

    ///**
    // * TROUBLESHOOTING ONLY.
    // */
    //key& operator=(const key& value)
    //{
    //    // TODO: change EC_KEY_copy to EC_KEY_dup
    //    //elliptic_curve_key& elliptic_curve_key::operator=(
    //    //    const elliptic_curve_key& other)
    //    //{
    //    //    key_ = EC_KEY_dup(other.key_);
    //    //    return *this;
    //    //}

    //    value_ = value.value_;
    //    return *this;
    //}

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, key& argument)
    {
        std::string hex;
        input >> hex;

        // TODO: determine how to properly raise error in deserialization.
        if (!read_public_or_private_key(argument.value_, hex))
            throw std::exception(SX_SERIALIZER_KEY_EXCEPTION);

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
        const key& argument)
    {
        output << bc::encode_hex(argument.value_.public_key());
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::elliptic_curve_key value_;
};

} // sx
} // serializer

#endif