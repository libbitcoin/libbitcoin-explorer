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
#ifndef BX_HD_KEY_HPP
#define BX_HD_KEY_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

/**
 * Serialization helper to serialize both public and private hd keys.
 */
class BCX_API hd_key
{
public:

    /**
     * Default constructor.
     */
    hd_key()
    {
    }
    
    /**
     * Initialization constructor.
     * @param[in]  base58  The value to initialize with.
     */
    hd_key(const std::string& base58);

    /**
     * Get the version/prefix of the key value.
     * @return  The version of the key.
     */
    uint32_t version() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const wallet::hd_key&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, hd_key& argument);

private:

    /**
     * The private key state of this object.
     */
    wallet::hd_key value_;
};

} // namespace config
} // namespace explorer
} // namespace libbitcoin

#endif
