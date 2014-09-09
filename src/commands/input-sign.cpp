/*
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
#include <explorer/commands/input-sign.hpp>

#include <iostream>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>
#include <explorer/primitives/base16.hpp>
#include <explorer/utility/utility.hpp>

using namespace bc;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

console_result input_sign::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto index = get_index_option();
    const auto hash_type = get_sighash_option();
    const data_chunk& nonce = get_nonce_argument();
    const tx_type& tx = get_transaction_argument();
    const auto& secret = get_ec_private_key_argument();
    const auto& script = get_prevout_script_argument();

    if (nonce.size() < minimum_seed_size)
    {
        error << BX_INPUT_SIGN_SHORT_NONCE << std::endl;
        return console_result::failure;
    }

    if (tx.inputs.size() < index)
    {
        error << BX_INPUT_SIGN_INDEX_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    data_chunk signature;
    if (!sign_transaction(signature, tx, index, script, secret, nonce, hash_type))
    {
        error << BX_INPUT_SIGN_FAILED << std::endl;
        return console_result::failure;
    }

    output << base16(signature) << std::endl;
    return console_result::okay;
}

