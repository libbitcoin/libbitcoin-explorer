/**
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#ifndef EC_PRIVATE_HPP
#define EC_PRIVATE_HPP

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between base16 string and ec_secret.
 */
class ec_private
{
public:

    /**
     * Default constructor.
     */
    ec_private();

    /**
     * Initialization constructor.
     * @param[in]  hexcode  The value to initialize with.
     */
    ec_private(const std::string& hexcode);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    ec_private(const bc::ec_secret& value);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    ec_private(const bc::hd_private_key& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    ec_private(const ec_private& other);

    /**
     * Return a reference to the data member.
     * @return  A reference to the object's internal data.
     */
    bc::ec_secret& data();

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const bc::ec_secret&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, ec_private& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const ec_private& argument);

private:

    /**
     * The state of this object.
     */
    bc::ec_secret value_;
};

} // explorer
} // primitives

#endif