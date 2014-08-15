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
#ifndef HD_PRIVATE_HPP
#define HD_PRIVATE_HPP

#include <iostream>
#include <string>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between hex string and hd_private_key.
 */
class hd_priv
{
public:

    /**
     * Default constructor.
     */
    hd_priv();

    /**
     * Initialization constructor.
     * @param[in]  base58  The value to initialize with.
     */
    hd_priv(const std::string& base58);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    hd_priv(const libwallet::hd_private_key& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    hd_priv(const hd_priv& other);

    /**
     * Return a reference to the data member.
     * @return  A reference to the object's internal data.
     */
    libwallet::hd_private_key& data();

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const libwallet::hd_private_key&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, hd_priv& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const hd_priv& argument);

private:

    /**
     * The state of this object.
     */
    libwallet::hd_private_key value_;
};

} // sx
} // serializer

#endif