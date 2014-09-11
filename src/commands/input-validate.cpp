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
#include <bitcoin/explorer/commands/input-validate.hpp>

#include <iostream>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result input_validate::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto index = get_index_option();
    const auto hash_type = get_sighash_option();
    const tx_type& tx = get_transaction_argument();
    const auto& public_key = get_ec_public_key_argument();
    const auto& script = get_script_code_argument();
    const auto& signature = get_signature_argument();

    if (tx.inputs.size() < index)
    {
        error << BX_INPUT_VALIDATE_INDEX_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    if (!valid_signature(tx, index, public_key, script, signature, hash_type))
    {
        // We do not return a failure here, as this is a validity test.
        output << BX_INPUT_VALIDATE_INDEX_INVALID_SIGNATURE << std::endl;
        return console_result::invalid;
    }

    output << BX_INPUT_VALIDATE_INDEX_VALID_SIGNATURE << std::endl;
    return console_result::okay;
}

