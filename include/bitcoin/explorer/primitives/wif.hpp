/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#ifndef BX_WIF_HPP
#define BX_WIF_HPP

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between base16 string and ec_secret.
 */
class wif
{
public:

    /**
     * Default constructor.
     */
    BCX_API wif();

    /**
     * Initialization constructor.
     * @param[in]  base58  The value to initialize with.
     */
    BCX_API wif(const std::string& base58);

    /**
     * Initialization constructor.
     * @param[in]  value       The value to initialize with.
     * @param[in]  compressed  The value is compressed.
     */
    BCX_API wif(const ec_secret& value, bool compressed);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    BCX_API wif(const wallet::hd_private_key& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    BCX_API wif(const wif& other);

    /**
     * Get the compressed property.
     */
    BCX_API bool get_compressed() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    BCX_API operator const ec_secret&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    BCX_API friend std::istream& operator>>(std::istream& input,
        wif& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    BCX_API friend std::ostream& operator<<(std::ostream& output,
        const wif& argument);

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
    ec_secret value_;
};

} // namespace primitives
} // namespace explorer
} // namespace libbitcoin

#endif
