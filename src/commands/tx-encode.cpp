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
#include <bitcoin/explorer/commands/tx-encode.hpp>

#include <iostream>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/transaction.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::config;
using namespace bc::wallet;

static bool push_scripts(std::vector<tx_output_type>& outputs,
    const explorer::config::output& output, uint8_t script_version)
{
    // explicit script
    if (!output.script().is_valid())
    {
        outputs.push_back({ output.amount(), output.script() });
        return true;
    }

    // If it's not explicit the script must be a form of pay to short hash.
    if (output.pay_to_hash() == null_short_hash)
        return false;

    chain::operation::list payment_ops;
    const auto hash = output.pay_to_hash();
    const auto is_stealth = !output.ephemeral_data().empty();

    // This presumes stealth versions are the same as non-stealth.
    if (output.version() != script_version)
        payment_ops = chain::script::to_pay_key_hash_pattern(hash);
    else if (output.version() == script_version)
        payment_ops = chain::script::to_pay_script_hash_pattern(hash);
    else
        return false;

    if (is_stealth)
    {
        // Stealth indexing requires an ordered script tuple.
        // The null data script must be pushed before the pay script.
        static constexpr uint64_t no_amount = 0;
        const auto data = output.ephemeral_data();
        const auto null_data = chain::script::to_null_data_pattern(data);
        const auto null_data_script = chain::script{ null_data };
        outputs.push_back({ no_amount, null_data_script });
    }

    const auto payment_script = chain::script{ payment_ops };
    outputs.push_back({ output.amount(), payment_script });
    return true;
}

console_result tx_encode::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto locktime = get_lock_time_option();
    const auto tx_version = get_version_option();
    const auto script_version = get_script_version_option();
    const auto& inputs = get_inputs_option();
    const auto& outputs = get_outputs_option();

    tx_type tx;
    tx.set_version(tx_version);
    tx.set_locktime(locktime);

    for (const tx_input_type& input: inputs)
        tx.inputs().push_back(input);

    for (const auto& output: outputs)
    {
        if (!push_scripts(tx.outputs(), output, script_version))
        {
            error << BX_TX_ENCODE_INVALID_OUTPUT << std::endl;
            return console_result::failure;
        }
    }

    if (tx.is_locktime_conflict())
    {
        error << BX_TX_ENCODE_LOCKTIME_CONFLICT << std::endl;
        return console_result::failure;
    }

    output << transaction(tx) << std::endl;
    return console_result::okay;
}
