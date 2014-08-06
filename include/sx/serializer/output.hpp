/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/script.hpp>
#include <sx/utility/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

    /**
     * Build the output script for the specified public key hash.
     *
     * @param[in]  pubkey_hash  The pubkey hash used to generate the script.
     * @return                  The resulting script.
     */
    static bc::script_type build_pubkey_hash_script(
        const bc::short_hash& pubkey_hash)
    {
        bc::script_type script;
        script.push_operation({ bc::opcode::dup, bc::data_chunk() });
        script.push_operation({ bc::opcode::hash160, bc::data_chunk() });
        script.push_operation({ bc::opcode::special, bc::data_chunk(
            pubkey_hash.begin(), pubkey_hash.end()) });
        script.push_operation({ bc::opcode::equalverify, bc::data_chunk() });
        script.push_operation({ bc::opcode::checksig, bc::data_chunk() });
        return script;
    }

    /**
     * Build the output script for the specified script hash.
     *
     * @param[in]  script_hash  The script hash used to generate the script.
     * @return                  The resulting script.
     */
    static bc::script_type build_script_hash_script(
        const bc::short_hash& script_hash)
    {
        bc::script_type script;
        script.push_operation({ bc::opcode::hash160, bc::data_chunk() });
        script.push_operation({ bc::opcode::special, bc::data_chunk(
            script_hash.begin(), script_hash.end()) });
        script.push_operation({ bc::opcode::equal, bc::data_chunk() });
        return script;
    }

    /**
     * Build the output script for the specified address.
     * This allows the input to be a single address as a shorthand for a 
     * script which is generated here deterministically from the address.
     *
     * @param[out] script   The resulting script.
     * @param[in]  address  The address from which the script is generated.
     * @return              True if successful.
     */
    static bool build_output_script(bc::script_type& script,
        const bc::payment_address& address)
    {
        switch (address.version())
        {
            case bc::payment_address::pubkey_version:
                script = build_pubkey_hash_script(address.hash());
                return true;

            case bc::payment_address::script_version:
                script = build_script_hash_script(address.hash());
                return true;
        }

        return false;
    }

    /**
     * Build the stealth metadata output.
     *
     * @param[in]  ephemeral_secret  The stealth payment ephemeral secret.
     * @return                       The stealth metadata output.
     */
    static bc::transaction_output_type build_stealth_meta_output(
        const bc::ec_secret& ephemeral_secret)
    {
        bc::transaction_output_type out;

        // TODO: review the purpose of prefix as it looks like a privacy leak.
        auto ephemeral_pubkey = bc::secret_to_public_key(ephemeral_secret);
        bc::data_chunk stealth_metadata{ { 0x06, 0x00, 0x00, 0x00, 0x00 } };
        bc::extend_data(stealth_metadata, ephemeral_pubkey);

        out.value = 0;
        out.script.push_operation({ bc::opcode::return_, bc::data_chunk() });
        out.script.push_operation({ bc::opcode::special, stealth_metadata });
        return out;
    }

    /**
     * Generate a new secret from the third token (seed).
     * Throws if output is invalid.
     *
     * @param[in]  tokens   The tokens to parse (at least two).
     * @return              The new elliptic curve secret.
     */
    static bc::ec_secret generate_private_key(
        const std::vector<std::string>& tokens)
    {
        bc::ec_secret seed;

        // This section can throw or produce a null secret.
        if (tokens.size() == 3)
        {
            size_t bitlength;
            deserialize(bitlength, tokens[2]);
            seed = new_key(new_seed(bitlength));
        }

        if (seed == bc::ec_secret())
            throw po::invalid_option_value(tokens[0]);

        return seed;
    }

    /**
     * Parse tokens into the transaction outputs. Throws if output is invalid.
     *
     * @param[out] outputs  The transaction outputs to populate.
     * @param[in]  tokens   The pre-validated two or three tokens to parse.
     * @return              The pay-to address or script.
     */
    static std::string parse_outputs(
        std::vector<bc::transaction_output_type>& outputs,
        const std::vector<std::string>& tokens)
    {
        auto& target = tokens[0];
        bc::transaction_output_type output;
        deserialize(output.value, tokens[1]);

        bc::payment_address pubkey_address;
        if (pubkey_address.set_encoded(target))
        {
            if (!build_output_script(output.script, pubkey_address))
                throw po::invalid_option_value(target);

            return pubkey_address.encoded();
        }

        libwallet::stealth_address stealth;
        if (stealth.set_encoded(target))
        {
            bool reuse = are_flags_set(stealth.options,
                libwallet::stealth_address::flags::reuse_key);

            // Prefix not yet supported, exactly one spend key is required.
            auto keys = if_else(reuse, 1, 0) + stealth.spend_pubkeys.size();
            if (keys != 1 || stealth.prefix.size() > 0)
                throw po::invalid_option_value(target);

            // Get scan and spend pubkeys.
            auto spend_pubkey = if_else(reuse, stealth.scan_pubkey,
                stealth.spend_pubkeys.front());

            // Do stealth stuff.
            auto ephemeral_secret = generate_private_key(tokens);
            auto public_key = libwallet::initiate_stealth(ephemeral_secret,
                stealth.scan_pubkey, spend_pubkey);

            // Add RETURN meta output.
            auto meta_output = build_stealth_meta_output(ephemeral_secret);
            outputs.push_back(meta_output);

            // Generate the address.
            bc::payment_address pay_address;
            bc::set_public_key(pay_address, public_key);

            if (!build_output_script(output.script, pay_address))
                throw po::invalid_option_value(target);

            return pay_address.encoded();
        }

        // Otherwise the token is assumed to be a hex-encoded script.
        output.script = script(target);

        outputs.push_back(output);
        return bc::pretty(output.script);
    }

/**
 * Serialization helper to convert between a base58-string:number and 
 * a vector of transaction_output_type.
 */
class output
{
public:

    /**
     * Constructor.
     */
    output()
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  tuple  The value to initialize with.
     */
    output(const std::string& tuple)
    {
        std::stringstream(tuple) >> *this;
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    output(const output& other)
        : value_(other.value_), pay_to_(other.pay_to_)
    {
    }

    /**
     * Return a reference to the pay-to data member.
     *
     * @return  A reference to the object's internal data.
     */
    const std::string& payto() const
    {
        return pay_to_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const std::vector<bc::transaction_output_type>&() const
    {
        return value_; 
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, output& argument)
    {
        std::string tuple;
        input >> tuple;

        std::vector<std::string> tokens;
        split(tuple, tokens, SX_TX_POINT_DELIMITER);
        if (tokens.size() != 2 && tokens.size() != 3)
            throw po::invalid_option_value(tuple);

        argument.value_.clear();
        argument.pay_to_ = parse_outputs(argument.value_, tokens);

        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   stream    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& stream,
        const output& argument)
    {
        // see bc::concat_point()
        // This does not retain the original serialized form.
        // Instead this serializes the last output, as hex encoded script.
        const auto& last = argument.value_.back();
        stream << script(last.script) << SX_TX_POINT_DELIMITER << last.value;
        return stream;
    }

private:

    /**
     * The transaction outputs state of this object.
     */
    std::vector<bc::transaction_output_type> value_;

    /**
     * The pay to address that matches the state of this object.
     */
    std::string pay_to_;
};

} // sx
} // serializer

#endif