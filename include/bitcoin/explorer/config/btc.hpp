/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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
#ifndef BX_BTC_HPP
#define BX_BTC_HPP

#include <cstdint>
#include <iostream>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

/**
 * Serialization helper to convert between btc and satoshi.
 */
class BCX_API btc
{
public:

    /**
     * Default constructor.
     */
    btc();

    /**
     * Initialization constructor.
     * @param[in]  btc  The number of btc to initialize with.
     */
    btc(const std::string& btc);

    /**
     * Initialization constructor.
     * @param[in]  satoshi  The number of satoshi to initialize with.
     */
    btc(uint64_t satoshi);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    btc(const btc& other);

    /**
     * Return a reference to the data member cast as satoshi.
     * @return  A reference to the object's internal data.
     */
    operator uint64_t() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input,
        btc& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const btc& argument);

private:

    /**
     * The state of this object's number of satoshis.
     */
    uint64_t value_;
};

} // namespace explorer
} // namespace config
} // namespace libbitcoin

#endif
