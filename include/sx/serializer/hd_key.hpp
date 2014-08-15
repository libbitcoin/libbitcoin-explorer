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
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hd_priv.hpp>
#include <sx/serializer/hd_pub.hpp>

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
     * Default onstructor.
     */
    hd_key();

    /**
     * Initialization constructor.
     * @param[in]  base58  The value to initialize with.
     */
    hd_key(const std::string& base58);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    hd_key(const libwallet::hd_private_key& value);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    hd_key(const libwallet::hd_public_key& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    hd_key(const hd_key& other);

    /**
     * Return a const reference to the public key of the private key if valid 
     * and otherwise return the public key.
     * @return  A reference to the object's internal data.
     */
    const libwallet::hd_public_key& derived_public_key() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const libwallet::hd_private_key&() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const libwallet::hd_public_key&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, hd_key& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const hd_key& argument);

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