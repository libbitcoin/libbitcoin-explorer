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

#include <bitcoin/explorer/commands/tx-encode.hpp>

#include <algorithm>
#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

console_result tx_encode::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto locktime = get_lock_time_option();
    const auto tx_version = get_version_option();
    const auto& inputs = get_inputs_option();
    const auto& outputs = get_outputs_option();

    const chain::transaction tx
    {
        tx_version,
        chain::inputs{ inputs.begin(), inputs.end() },
        chain::outputs{ outputs.begin(), outputs.end() },
        locktime
    };

    if (!tx.is_valid())
    {
        error << BX_TX_ENCODE_INVALID_OUTPUT << std::endl;
        return console_result::failure;
    }

    const auto& ins = *tx.inputs_ptr();

    // Locktime is ineffective if all sequences are maximal.
    if (!is_zero(locktime) && std::all_of(ins.begin(), ins.end(),
        [](const auto& in) NOEXCEPT
        {
            return in->is_final();
        }))
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
