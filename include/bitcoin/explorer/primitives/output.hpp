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
#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Build the output script for the specified public key hash.
 * @param[in]  pubkey_hash  The pubkey hash used to generate the script.
 * @return                  The resulting script.
 */
static script_type build_pubkey_hash_script(
    const short_hash& pubkey_hash);

/**
 * Build the output script for the specified script hash.
 * @param[in]  script_hash  The script hash used to generate the script.
 * @return                  The resulting script.
 */
static script_type build_script_hash_script(
    const short_hash& script_hash);

/**
 * Build the output script for the specified address.
 * This allows the input to be a single address as a shorthand for a 
 * script which is generated here deterministically from the address.
 * @param[out] script   The resulting script.
 * @param[in]  address  The address from which the script is generated.
 * @return              True if successful.
 */
static bool build_output_script(script_type& script,
    const payment_address& address);

/**
 * Build the stealth metadata output.
 * @param[in]  ephemeral_secret  The stealth payment ephemeral secret.
 * @return                       The stealth metadata output.
 */
static tx_output_type build_stealth_meta_output(
    const ec_secret& ephemeral_secret);

/**
 * Generate a new secret from the third token (seed).
 * @param[in]  tokens   The tokens to parse (at least two).
 * @return              The new elliptic curve secret or null_hash.
 */
static ec_secret generate_private_key(
    const std::vector<std::string>& tokens);

/**
 * Parse tokens into the transaction outputs. Throws if output is invalid.
 * The list of outputs is cleared before processing.
 * @param[out] outputs  The transaction outputs to populate.
 * @param[in]  tokens   The pre-validated two or three tokens to parse.
 * @return              The pay-to address or script.
 */
static std::string parse_outputs(
    std::vector<tx_output_type>& outputs,
    const std::vector<std::string>& tokens);

/**
 * Serialization helper to convert between a base58-string:number and 
 * a vector of tx_output_type.
 */
class output
{
public:

    /**
     * Default constructor.
     */
    BCX_API output();

    /**
     * Initialization constructor.
     * @param[in]  tuple  The value to initialize with.
     */
    BCX_API output(const std::string& tuple);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    BCX_API output(const tx_output_type& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    BCX_API output(const output& other);

    /**
     * Return a reference to the pay-to data member.
     * @return  A reference to the object's internal data.
     */
    BCX_API const std::string& payto() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    BCX_API operator const std::vector<tx_output_type>&() const;

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
        output& argument);

    /**
     * Overload stream out.
     * @param[in]   stream    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    BCX_API friend std::ostream& operator<<(std::ostream& stream,
        const output& argument);

private:

    /**
     * The transaction outputs state of this object. We use a vector to capture
     * the meta-output required for stealth and potentially other scenarios.
     */
    std::vector<tx_output_type> value_;

    /**
     * The pay to address that matches the state of this object.
     */
    std::string pay_to_;
};

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin

#endif