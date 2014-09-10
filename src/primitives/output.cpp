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
#include "precompile.hpp"
#include <explorer/primitives/output.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/prop_tree.hpp>
#include <explorer/primitives/base16.hpp>
#include <explorer/primitives/point.hpp>
#include <explorer/primitives/script.hpp>
#include <explorer/utility/utility.hpp>

using namespace po;
using namespace pt;

namespace libbitcoin {
namespace explorer {
namespace primitives {

static script_type build_pubkey_hash_script(
    const short_hash& pubkey_hash)
{
    script_type script;
    script.push_operation({ opcode::dup, data_chunk() });
    script.push_operation({ opcode::hash160, data_chunk() });
    script.push_operation({ opcode::special, data_chunk(
        pubkey_hash.begin(), pubkey_hash.end()) });
    script.push_operation({ opcode::equalverify, data_chunk() });
    script.push_operation({ opcode::checksig, data_chunk() });
    return script;
}

static script_type build_script_hash_script(
    const short_hash& script_hash)
{
    script_type script;
    script.push_operation({ opcode::hash160, data_chunk() });
    script.push_operation({ opcode::special, data_chunk(
        script_hash.begin(), script_hash.end()) });
    script.push_operation({ opcode::equal, data_chunk() });
    return script;
}

static bool build_output_script(script_type& script,
    const payment_address& address)
{
    switch (address.version())
    {
        case payment_address::pubkey_version:
            script = build_pubkey_hash_script(address.hash());
            return true;

        case payment_address::script_version:
            script = build_script_hash_script(address.hash());
            return true;
    }

    return false;
}

static tx_output_type build_stealth_meta_output(
    const ec_secret& ephemeral_secret)
{
    tx_output_type out;

    // NOTE: The version and fixed-length nonce both reduce privacy.
    constexpr uint8_t nonce = 0x00;
    constexpr uint8_t version = 0x06;

    auto ephemeral_pubkey = secret_to_public_key(ephemeral_secret);
    data_chunk stealth_metadata{ { version, nonce, nonce, nonce, nonce } };
    extend_data(stealth_metadata, ephemeral_pubkey);

    out.value = 0;
    out.script.push_operation({ opcode::return_, data_chunk() });
    out.script.push_operation({ opcode::special, stealth_metadata });
    return out;
}

static ec_secret generate_private_key(
    const std::vector<std::string>& tokens)
{
    if (tokens.size() == 3)
    {
        data_chunk seed = base16(tokens[2]);
        if (seed.size() >= minimum_seed_size)
            return new_key(seed);
    }

    return null_hash;
}

static std::string parse_outputs(
    std::vector<tx_output_type>& outputs,
    const std::vector<std::string>& tokens)
{
    outputs.clear();
    auto& target = tokens[0];
    tx_output_type output;
    deserialize(output.value, tokens[1]);

    payment_address address;
    if (address.set_encoded(target))
    {
        if (!build_output_script(output.script, address))
            throw invalid_option_value(target);

        return address.encoded();
    }

    stealth_address stealth;
    if (stealth.set_encoded(target))
    {
        auto scan_pubkey = stealth.get_scan_pubkey();
        auto spend_pubkeys = stealth.get_spend_pubkeys();

        // Prefix not yet supported, exactly one spend key is required.
        auto keys = spend_pubkeys.size();
        if (keys != 1 || stealth.get_prefix().size() > 0)
            throw invalid_option_value(target);
        
        // Do stealth stuff.
        auto ephemeral_secret = generate_private_key(tokens);
        if (ephemeral_secret == null_hash)
            throw invalid_option_value(target);

        // We have already ensured there is exactly one spend key.
        auto public_key = initiate_stealth(ephemeral_secret, scan_pubkey,
            spend_pubkeys.front());

        // Add RETURN meta output.
        auto meta_output = build_stealth_meta_output(ephemeral_secret);
        outputs.push_back(meta_output);

        // Generate the address.
        payment_address pay_address;
        set_public_key(pay_address, public_key);
        if (!build_output_script(output.script, pay_address))
            throw invalid_option_value(target);

        return pay_address.encoded();
    }

    // Otherwise the token is assumed to be a base16-encoded script.
    output.script = script(target);

    outputs.push_back(output);
    return pretty(output.script);
}

output::output()
    : value_()
{
}

output::output(const std::string& tuple)
{
    std::stringstream(tuple) >> *this;
}

output::output(const tx_output_type& value)
{
    value_.clear();
    value_.push_back(value);
}

output::output(const output& other)
    : value_(other.value_), pay_to_(other.pay_to_)
{
}

const std::string& output::payto() const
{
    return pay_to_;
}

output::operator const std::vector<tx_output_type>&() const
{
    return value_; 
}

output::operator const ptree() const
{
    return prop_tree(value_);
}

std::istream& operator>>(std::istream& input, output& argument)
{
    std::string tuple;
    input >> tuple;

    std::vector<std::string> tokens;
    split(tuple, tokens, BX_TX_POINT_DELIMITER);
    if (tokens.size() != 2 && tokens.size() != 3)
        throw invalid_option_value(tuple);

    argument.pay_to_ = parse_outputs(argument.value_, tokens);
    return input;
}

std::ostream& operator<<(std::ostream& stream, const output& argument)
{
    // This does not retain the original serialized form.
    // Instead this serializes the last output, as base16 encoded script.
    const auto& last = argument.value_.back();
    stream << script(last.script) << BX_TX_POINT_DELIMITER << last.value;
    return stream;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
