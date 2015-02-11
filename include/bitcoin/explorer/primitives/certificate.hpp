/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
#ifndef BX_CERTIFICATE_HPP
#define BX_CERTIFICATE_HPP

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between data_chunk and Z85 text.
 */
class certificate
{
public:

    /**
     * Default constructor.
     */
    BCX_API certificate();

    /**
     * Initialization constructor.
     * @param[in]  base85  The value to initialize with.
     */
    BCX_API certificate(const std::string& base85);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    BCX_API certificate(const certificate& other);

    /**
     * Convert internal type to text string.
     * Returns empty string if not initialized.
     * @return  This object's value cast to a Z85 encoded string.
     */
    BCX_API std::string get_base85() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    BCX_API operator const data_chunk&() const;

    /**
     * Overload cast to generic data reference.
     * @return  This object's value cast to a generic data reference.
     */
    BCX_API operator data_slice() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    BCX_API friend std::istream& operator>>(std::istream& input,
        certificate& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    BCX_API friend std::ostream& operator<<(std::ostream& output,
        const certificate& argument);

private:

    /**
     * The state of this object.
     */
    data_chunk value_;
};

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin

#endif
