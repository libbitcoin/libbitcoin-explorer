/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BX_ADDRESS_HPP
#define BX_ADDRESS_HPP

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

/**
 * Serialization helper to convert between base58 string and bitcoin payment
 * and stealth address.
 */
class BCX_API address
{
public:

    /**
     * Default constructor.
     */
    address()
    {
    }

    /**
     * Initialization constructor.
     * @param[in]  base58  The value to initialize with.
     */
    address(const std::string& base58);

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type reference.
     */
    operator const std::string&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input,
        address& argument);

private:

    /**
     * The state of this object.
     */
    std::string value_;
};

} // namespace explorer
} // namespace config
} // namespace libbitcoin

#endif
