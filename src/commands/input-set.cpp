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
#include <explorer/commands/input-set.hpp>

#include <iostream>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>
#include <explorer/primitives/transaction.hpp>
#include <explorer/utility/utility.hpp>

using namespace bc;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

console_result input_set::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto index = get_index_option();
    const auto& transaction_original = get_transaction_argument();
    const auto& script = get_signature_and_pubkey_script_argument();

    // Clone so we can keep arguments const.
    auto transaction_copy = transaction(transaction_original);
    auto& tx = transaction_copy.data();

    if (tx.inputs.size() < index)
    {
        error << BX_INPUT_SET_INDEX_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    tx.inputs[index].script = script_to_raw_data_script(script);

    output << transaction_copy << std::endl;
    return console_result::okay;
}