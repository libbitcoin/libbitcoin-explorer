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
#ifndef BX_WRAPPER_HPP
#define BX_WRAPPER_HPP

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between a checksum'd wrapper and data_chunk.
 */
class wrapper
{
public:

    /**
     * Default constructor.
     */
    BCX_API wrapper();

    /**
     * Initialization constructor.
     * 
     * @param[in]  wrapped  The value to initialize with.
     */
    BCX_API wrapper(const std::string& wrapped);

    /**
     * Initialization constructor.
     * @param[in]  wrapped  The wrapped value to initialize with.
     */
    BCX_API wrapper(const data_chunk& wrapped);

    /**
     * Initialization constructor.
     * @param[in]  wrapped  The wrapped value to initialize with.
     */
    BCX_API wrapper(const wrapped_data& wrapped);

    /**
     * Initialization constructor.
     * @param[in]  address  The payment address to initialize with.
     */
    BCX_API wrapper(const payment_address& address);

    /**
     * Initialization constructor.
     * @param[in]  version  The version for the new wrapped value.
     * @param[in]  payload  The payload for the new wrapped value.
     */
    BCX_API wrapper(uint32_t version, const data_chunk& payload);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    BCX_API wrapper(const wrapper& other);

    /**
     * Overload cast to the wrapped value.
     * @return  This object's wrapped data cast to data chunk.
     */
    BCX_API operator const data_chunk() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    BCX_API operator const wrapped_data&() const;

    /**
     * Overload cast to property tree.
     * @return  This object's value cast to a property tree.
     */
    BCX_API operator const pt::ptree() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    BCX_API friend std::istream& operator>>(std::istream& input,
        wrapper& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    BCX_API friend std::ostream& operator<<(std::ostream& output,
        const wrapper& argument);

private:

    /**
     * The state of this object's data.
     */
    wrapped_data value_;
};

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin

#endif