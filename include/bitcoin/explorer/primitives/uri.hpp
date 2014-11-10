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
#ifndef BX_URI_HPP
#define BX_URI_HPP

#include <iostream>
#include <string>
#include <cstdint>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between string and uri_parse_result.
 */
class uri
{
public:

    /**
     * Default constructor.
     */
    BCX_API uri();

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    BCX_API uri(const std::string& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    BCX_API uri(const uri& other);

    /**
     * Overload cast to property tree.
     * @return  This object's value cast to a property tree.
     */
    BCX_API operator const pt::ptree() const;

    /**
     * Overload cast to string.
     * @return  This object's value cast to a string.
     */
    BCX_API operator const std::string() const;

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    BCX_API friend std::istream& operator>>(std::istream& input,
        uri& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    BCX_API friend std::ostream& operator<<(std::ostream& output,
        const uri& argument);

private:

    /**
     * The state of this object.
     */
    std::string value_;
};

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin

#endif
