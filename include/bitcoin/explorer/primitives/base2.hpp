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
#ifndef BX_BASE3_HPP
#define BX_BASE3_HPP

#include <iostream>
#include <string>
#include <cstdint>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between binary string and bitset.
 */
class BCX_API base2
{
public:

    /**
     * Default constructor.
     */
    base2();

    /**
     * Initialization constructor.
     * @param[in]  bin  The value to initialize with.
     */
    base2(const std::string& binary);

    /**
     * @param[in]  value  The value to initialize with.
     */
    base2(const bc::binary_type& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    base2(const base2& other);

    /**
     * Get number of bits in value.
     */
    size_t size() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const bc::binary_type&() const;

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input,
        base2& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const base2& argument);

private:

    /**
     * The state of this object.
     */
    bc::binary_type value_;
};

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin

#endif
