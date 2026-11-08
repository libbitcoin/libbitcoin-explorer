/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/input-set.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

console_result input_set::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto index = get_index_option();
    const chain::transaction& tx = get_transaction_argument();
    const chain::script& endorsement = get_endorsement_script_argument();
    const chain::witness& witness = get_witness_option();

    const auto& ins = *tx.inputs_ptr();

    if (index >= ins.size())
    {
        error << BX_INPUT_SET_INDEX_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    const auto inputs = to_shared<chain::input_cptrs>();
    inputs->reserve(ins.size());

    for (size_t input{}; input < ins.size(); ++input)
    {
        if (input != index)
        {
            inputs->push_back(ins[input]);
            continue;
        }

        const auto witness_cptr = witness.is_valid() ?
            to_shared<chain::witness>(witness) : ins[input]->witness_ptr();

        inputs->push_back
        (
            to_shared<chain::input>
            (
                ins[input]->point_ptr(),
                to_shared<chain::script>(endorsement),
                witness_cptr,
                ins[input]->sequence()
            )
        );
    }

    output << transaction(chain::transaction
    {
        tx.version(),
        inputs,
        tx.outputs_ptr(),
        tx.locktime()
    }) << std::endl;

    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
