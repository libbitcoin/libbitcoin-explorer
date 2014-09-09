/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
#ifndef STEALTH_HPP
#define STEALTH_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/ec_public.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between a stealth address and a base16 string.
 */
class stealth
{
public:

    /**
     * Default constructor.
     */
    stealth();

    /**
     * Initialization constructor.
     * 
     * @param[in]  base58  The value to initialize with.
     */
    stealth(const std::string& base58);

    /**
     * Initialization constructor.
     * @param[in]  address  The value to initialize with.
     */
    stealth(const bc::stealth_address& address);

    /**
     * Initialization constructor.
     * @param[in]  prefix      The stealth prefix (bitfield and number_bits).
     * @param[in]  scan_key    The stealth scan public key.
     * @param[in]  spend_keys  The set of spend keys (limited to 255). Defaults
                               To the value of the scan key (otherwise the scan
                               key must be added explicitly).
     * @param[in]  signatures  The number of signatures required to spend. 
     *                         If zero spend will require all spend keys sign.
     * @param[in]  testnet     The stealth address will be for testnet.
     */
    stealth(const bc::stealth_prefix& prefix, const ec_public& scan_key,
        const std::vector<ec_public>& spend_keys, uint8_t signatures, 
        bool testnet);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    stealth(const stealth& other);

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const bc::stealth_address&() const;

    /**
     * Overload cast to property tree.
     * @return  This object's value cast to a property tree.
     */
    operator const pt::ptree() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, stealth& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, 
        const stealth& argument);

private:

    /**
     * The state of this object's data.
     */
    bc::stealth_address value_;
};

} // explorer
} // primitives

#endif