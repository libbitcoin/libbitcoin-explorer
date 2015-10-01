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
#include <bitcoin/explorer/primitives/output.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

output::output()
  : amount_(0), payment_version_(0), stealth_version_(0), script_(),
    pay_to_hash_(null_short_hash), ephemeral_script_data_({})
{
}

output::output(const std::string& tuple)
  : output()
{
    std::stringstream(tuple) >> *this;
}

uint64_t output::amount() const
{
    return amount_;
}

uint8_t output::payment_version() const
{
    return payment_version_;
}

uint8_t output::stealth_version() const
{
    return stealth_version_;
}

chain::script output::script() const
{
    return script_;
}

short_hash output::pay_to_hash() const
{
    return pay_to_hash_;
}

const data_chunk& output::ephemeral_script_data() const
{
    return ephemeral_script_data_;
}

std::istream& operator>>(std::istream& input, output& argument)
{
    std::string tuple;
    input >> tuple;

    const auto tokens = split(tuple, BX_TX_POINT_DELIMITER);
    if (tokens.size() < 2 || tokens.size() > 3)
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(tuple));
    }

    uint64_t amount;
    deserialize(amount, tokens[1], true);
    if (amount > max_money())
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(tuple));
    }

    argument.amount_ = amount;
    const auto& target = tokens.front();

    // Is the target a payment address?
    const wallet::payment_address payment(target);
    if (payment)
    {
        argument.payment_version_ = payment.version();
        argument.pay_to_hash_ = payment.hash();
        return input;
    }

    // Is the target a stealth address?
    const wallet::stealth_address stealth(target);
    if (stealth)
    {
        // TODO: finish stealth multisig implemetation and remove this guard.
        if (stealth.spend_keys().size() != 1 ||
            tokens.size() != 3 || tokens[2].size() < minimum_seed_size * 2)
        {
            BOOST_THROW_EXCEPTION(invalid_option_value(target));
        }

        data_chunk seed;
        if (!decode_base16(seed, tokens[2]))
        {
            BOOST_THROW_EXCEPTION(invalid_option_value(target));
        }

        ec_secret ephemeral_secret;
        ec_compressed ephemeral_point;
        data_chunk ephemeral_script_data;
        if (!create_shealth_script(ephemeral_script_data, ephemeral_secret,
            ephemeral_point, stealth.filter(), seed))
        {
            BOOST_THROW_EXCEPTION(invalid_option_value(target));
        }

        ec_compressed stealth_key;
        if (!uncover_stealth(stealth_key, stealth.scan_key(), ephemeral_secret,
            stealth.spend_keys().front()))
        {
            BOOST_THROW_EXCEPTION(invalid_option_value(target));
        }

        // TODO: implement support for stealth multisig (p2sh) above.
        // This implies only p2kh support, need to hash the multisig script.
        argument.pay_to_hash_ = bitcoin_short_hash(stealth_key);
        argument.ephemeral_script_data_ = ephemeral_script_data;

        // TODO: align with payment version and use here instead.
        argument.stealth_version_ = stealth.version();
        return input;
    }

    // The target must be a serialized script.
    argument.script_ = script(target);
    return input;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
