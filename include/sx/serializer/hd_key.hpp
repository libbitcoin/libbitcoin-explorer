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
#ifndef HD_KEY_HPP
#define HD_KEY_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hd_private.hpp>
#include <sx/serializer/hd_public.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between hex string and ec_point.
 * Reads public or private key and writes corresponding public key.
 */
class hd_key
{
public:

    /**
     * Constructor.
     */
    hd_key()
        : private_key_value_(), public_key_value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  arg  The value to initialize with.
     */
    hd_key(const std::string& arg)
    {
        std::stringstream(arg) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    hd_key(const libwallet::hd_private_key& value)
    {
        // hd_public_key doesn't provide a copy constructor.
        private_key_value_.deserialize(value.serialize());
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    hd_key(const libwallet::hd_public_key& value)
    {
        // hd_public_key doesn't provide a copy constructor.
        public_key_value_.deserialize(value.serialize());
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    hd_key(const hd_key& other)
    {
        public_key_value_ = other.public_key_value_;
        private_key_value_ = other.private_key_value_;
    }

    /**
     * Return a const reference to the public key of the private key if valid 
     * and otherwise return the public key.
     *
     * @return  A reference to the object's internal data.
     */
    const libwallet::hd_public_key& derived_public_key() const
    {
        if (private_key_value_.valid())
            return (libwallet::hd_public_key&)private_key_value_;
        else
            return public_key_value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const libwallet::hd_private_key&() const
    {
        return private_key_value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const libwallet::hd_public_key&() const
    {
        return public_key_value_;
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, hd_key& argument)
    {
        std::string text;
        input >> text;

        // First try to read as a private key.
        if (!argument.private_key_value_.deserialize(text))
        {
            // Otherwise try to read as a public key.
            if (!argument.public_key_value_.deserialize(text))
                throw po::invalid_option_value(text);
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
        const hd_key& argument)
    {
        const auto& public_key = argument.derived_public_key();
        output << public_key.serialize();
        return output;
    }

private:

    /**
     * The private key state of this object.
     */
    libwallet::hd_private_key private_key_value_;

    /**
    * The public key state of this object.
    */
    libwallet::hd_public_key public_key_value_;
};

} // sx
} // serializer

#endif