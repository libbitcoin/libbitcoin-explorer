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
#include <sx/utility/coin.hpp>

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
        : value_() {}

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
        value_.set_serialized(value.serialize());
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    hd_key(const libwallet::hd_public_key& value)
    {
        // hd_public_key doesn't provide a copy constructor.
        value_.set_serialized(value.serialize());
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    hd_key(const hd_key& other)
        : hd_key(other.value_) {}

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const libwallet::hd_private_key() const
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const libwallet::hd_public_key() const
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
    friend std::istream& operator>>(std::istream& input, hd_key& argument)
    {
        std::string text;
        input >> text;

        try
        {
            // First try to read as a private key.
            libwallet::hd_private_key private_key = hd_private(text);
            argument.value_.set_serialized(private_key.serialize());
        }
        catch (po::invalid_option_value)
        {
            // Otherwise try to read as a public key.
            libwallet::hd_public_key public_key = hd_public(text);
            argument.value_.set_serialized(public_key.serialize());
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
        output << hd_public(argument.value_);
        return output;
    }

private:

    /**
     * The state of this object.
     */
    libwallet::hd_private_key value_;
};

} // sx
} // serializer

#endif