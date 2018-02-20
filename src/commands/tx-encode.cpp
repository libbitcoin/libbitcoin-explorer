/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/tx-encode.hpp>

#include <iostream>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::config;
using namespace bc::wallet;

static bool push_scripts(std::vector<tx_output_type>& outputs,
    const bc::config::output& output, uint8_t script_version)
{
    static constexpr uint64_t no_amount = 0;

    // explicit script
    if (!output.is_stealth() && output.script().is_valid())
    {
        outputs.push_back({ output.amount(), output.script() });
        return true;
    }

    // If it's not explicit the script must be a form of pay to short hash.
    if (output.pay_to_hash() == null_short_hash)
        return false;

    machine::operation::list payment_ops;
    const auto hash = output.pay_to_hash();

    // This presumes stealth versions are the same as non-stealth.
    if (output.version() != script_version)
        payment_ops = chain::script::to_pay_key_hash_pattern(hash);
    else if (output.version() == script_version)
        payment_ops = chain::script::to_pay_script_hash_pattern(hash);
    else
        return false;

    // If stealth add null data stealth output immediately before payment.
    if (output.is_stealth())
        outputs.push_back({ no_amount, output.script() });

    outputs.push_back({ output.amount(), { payment_ops } });
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

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
