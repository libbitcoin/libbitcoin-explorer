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
#include <bitcoin/explorer/primitives/output.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/point.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

static chain::script build_pubkey_hash_script(const short_hash& pubkey_hash)
{
    data_chunk hash(pubkey_hash.begin(), pubkey_hash.end());

    chain::operation::stack ops = {
        chain::operation{ chain::opcode::dup, data_chunk() },
        chain::operation{ chain::opcode::hash160, data_chunk() },
        chain::operation{ chain::opcode::special, hash },
        chain::operation{ chain::opcode::equalverify, data_chunk() },
        chain::operation{ chain::opcode::checksig, data_chunk() }
    };

    return chain::script{ ops };
}

static chain::script build_script_hash_script(const short_hash& script_hash)
{
    data_chunk hash(script_hash.begin(), script_hash.end());

    chain::operation::stack ops = {
        chain::operation{ chain::opcode::hash160, data_chunk() },
        chain::operation{ chain::opcode::special, hash },
        chain::operation{ chain::opcode::equal, data_chunk() }
    };

    return chain::script{ ops };
}

static bool build_output_script(chain::script& script,
    const wallet::payment_address& address)
{
    switch (address.version())
    {
        case wallet::payment_address::pubkey_version:
            script = build_pubkey_hash_script(address.hash());
            return true;

        case wallet::payment_address::script_version:
            script = build_script_hash_script(address.hash());
            return true;
    }

    return false;
}

static tx_output_type build_stealth_meta_output(
    const ec_secret& ephemeral_secret)
{
    // NOTE: The version and fixed-length nonce both reduce privacy.
    constexpr uint8_t nonce = 0x00;
    constexpr uint8_t version = 0x06;

    auto ephemeral_pubkey = secret_to_public_key(ephemeral_secret);
    data_chunk stealth_metadata{ { version, nonce, nonce, nonce, nonce } };
    extend_data(stealth_metadata, ephemeral_pubkey);

    chain::operation::stack ops = {
        chain::operation{ chain::opcode::return_, data_chunk() },
        chain::operation{ chain::opcode::special, stealth_metadata }
    };

    tx_output_type out{ 0, chain::script{ ops } };

    return out;
}

static ec_secret generate_private_key(const std::vector<std::string>& tokens)
{
    if (tokens.size() == 3)
    {
        data_chunk seed = base16(tokens[2]);
        if (seed.size() >= minimum_seed_size)
            return new_key(seed);
    }

    return null_hash;
}

// output is currently a private encoding in bx.
static bool decode_outputs(std::vector<tx_output_type>& outputs,
    std::string& pay_address, const std::string& tuple)
{
    std::vector<tx_output_type> result;

    const auto tokens = split(tuple, BX_TX_POINT_DELIMITER);
    if (tokens.size() != 2 && tokens.size() != 3)
        return false;

    auto& target = tokens[0];
    tx_output_type output;
    deserialize(output.value, tokens[1], true);

    wallet::payment_address pay_to_address;
    if (pay_to_address.from_string(target))
    {
        if (!build_output_script(output.script, pay_to_address))
        {
            BOOST_THROW_EXCEPTION(invalid_option_value(target));
        }

        result.push_back(output);
        outputs = result;
        pay_address = pay_to_address.to_string();
        return true;
    }

    wallet::stealth_address stealth;
    if (stealth.from_string(target))
    {
        auto scan_pubkey = stealth.get_scan_pubkey();
        auto spend_pubkeys = stealth.get_spend_pubkeys();

        // Prefix not yet supported, exactly one spend key is required.
        auto keys = spend_pubkeys.size();
        if (keys != 1 || stealth.get_prefix().size() > 0)
        {
            BOOST_THROW_EXCEPTION(invalid_option_value(target));
        }
        
        // Do stealth stuff.
        auto ephemeral_secret = generate_private_key(tokens);
        if (ephemeral_secret == null_hash)
        {
            BOOST_THROW_EXCEPTION(invalid_option_value(target));
        }

        // We have already ensured there is exactly one spend key.
        auto public_key = wallet::uncover_stealth(scan_pubkey,
            ephemeral_secret, spend_pubkeys.front());

        // Add RETURN meta output.
        auto meta_output = build_stealth_meta_output(ephemeral_secret);
        result.push_back(meta_output);

        // Generate the address.
        wallet::payment_address pay_to_address;
        pay_to_address.set_public_key(public_key);
        if (!build_output_script(output.script, pay_to_address))
        {
            BOOST_THROW_EXCEPTION(invalid_option_value(target));
        }

        result.push_back(output);
        outputs = result;
        pay_address = pay_to_address.to_string();
        return true;
    }

    // Otherwise the token is assumed to be a base16-encoded script.
    output.script = script(target);

    result.push_back(output);
    outputs = result;
    pay_address = output.script.to_string();
    return true;
}

// output is currently a private encoding in bx.
// This does not retain the original serialized form.
// It serializes the last output, as base16 encoded script.
static std::string encode_outputs(const std::vector<tx_output_type>& outputs)
{
    std::stringstream result;
    const auto& last = outputs.back();
    result << script(last.script) << BX_TX_POINT_DELIMITER << last.value;
    return result.str();
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

std::istream& operator>>(std::istream& input, output& argument)
{
    std::string tuple;
    input >> tuple;

    if (!decode_outputs(argument.value_, argument.pay_to_, tuple))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(tuple));
    }

    return input;
}

std::ostream& operator<<(std::ostream& stream, const output& argument)
{
    // This does not retain the original serialized form.
    // It serializes the last output, as base16 encoded script.
    stream << encode_outputs(argument.value_);
    return stream;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
