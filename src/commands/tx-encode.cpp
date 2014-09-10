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
#include <explorer/commands/tx-encode.hpp>

#include <iostream>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/input.hpp>
#include <explorer/primitives/output.hpp>
#include <explorer/primitives/transaction.hpp>
#include <explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result tx_encode::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto locktime = get_lock_time_option();
    const auto version = get_version_option();
    const auto& inputs = get_inputs_option();
    const auto& outputs = get_outputs_option();
    const auto& file = get_transaction_argument();

    tx_type tx;
    tx.version = version;
    tx.locktime = locktime;

    for (const tx_input_type& input: inputs)
        tx.inputs.push_back(input);

    for (const std::vector<tx_output_type>& output_sets: outputs)
        for (const auto& output: output_sets)
            tx.outputs.push_back(output);

    if (is_locktime_conflict(tx))
        error << BX_TX_ENCODE_LOCKTIME_CONFLICT << std::endl;

    write_file(output, file, transaction(tx));

    return console_result::okay;
}