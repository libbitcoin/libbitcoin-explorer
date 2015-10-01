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
#ifndef BX_OUTPUT_HPP
#define BX_OUTPUT_HPP

#include <iostream>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between a base58-string:number and 
 * a vector of tx_output_type.
 */
class BCX_API output
{
public:

    /**
     * Default constructor.
     */
    output();

    /**
     * Initialization constructor.
     * @param[in]  tuple  The value to initialize with.
     */
    output(const std::string& tuple);

    /// Parsed properties
    uint64_t amount() const;
    uint8_t payment_version() const;
    uint8_t stealth_version() const;
    const chain::script& script() const;
    const short_hash& pay_to_hash() const;
    const data_chunk& ephemeral_script_data() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input,
        output& argument);

private:

    /**
     * The transaction output state of this object.
     * This data is translated to an output given expected version information.
     */
    uint64_t amount_;
    uint8_t payment_version_;
    uint8_t stealth_version_;
    chain::script script_;
    short_hash pay_to_hash_;
    data_chunk ephemeral_script_data_;
};

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin

#endif
