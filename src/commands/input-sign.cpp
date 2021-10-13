/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/input-sign.hpp>

#include <iostream>
#include <cstdint>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

// The BX_INPUT_SIGN_FAILED condition uncovered by test.
// This is because a vector to produce the failure is not known.
console_result input_sign::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto anyone_can_pay = get_anyone_option();
    const auto index = get_index_option();
    const auto sign_type = get_sign_type_option();
    const tx_type& tx = get_transaction_argument();
    const ec_secret& private_key = get_ec_private_key_argument();
    const script& contract = get_contract_argument();

    if (index >= tx.inputs().size())
    {
        error << BX_INPUT_SIGN_INDEX_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    uint8_t hash_type = (machine::sighash_algorithm)sign_type;
    if (anyone_can_pay)
        hash_type |= machine::sighash_algorithm::anyone_can_pay;

    endorsement endorse;
    if (!chain::script::create_endorsement(endorse, private_key, contract, tx,
        index, hash_type))
    {
        error << BX_INPUT_SIGN_FAILED << std::endl;
        return console_result::failure;
    }

    output << base16(endorse) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
