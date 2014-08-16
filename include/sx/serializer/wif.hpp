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
#ifndef WIF_HPP
#define WIF_HPP

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between base16 string and ec_secret.
 */
class wif
{
public:

    /**
     * Default constructor.
     */
    wif();

    /**
     * Initialization constructor.
     * @param[in]  base58  The value to initialize with.
     */
    wif(const std::string& base58);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    wif(const bc::ec_secret& value);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    wif(const libwallet::hd_private_key& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    wif(const wif& other);

    /**
     * Return a reference to the data member.
     * @return  A reference to the object's internal data.
     */
    bc::ec_secret& data();

    /**
     * Get the compressed property.
     */
    bool get_compressed() const;

    /**
     * Set the compressed property.
     */
    void set_compressed(bool value);

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
    friend std::istream& operator>>(std::istream& input, wif& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, const wif& argument);

private:

    /**
     * The state of derived public key compression, indicating that the derived
     * public key should be compressed when serialized. This is obtained from
     * and serialized with the WIF private key and otherwise defaults to true.
     * https://bitcointalk.org/index.php?topic=129652.msg1384929#msg1384929
     */
    bool compressed_;

    /**
     * The state of this object's secret.
     */
    bc::ec_secret value_;
};

} // sx
} // serializer

#endif