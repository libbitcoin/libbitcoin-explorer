/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <sx/command/send-tx.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/callback_state.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;

static void handle_callback(callback_state& state)
{
    state.output(boost::format(SX_SEND_TX_OUTPUT) % now());
    state.stop();
}

console_result send_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& transactions = get_transactions_argument();

    callback_state state(error, output);
    const auto handler = [&state](const std::error_code& code)
    {
        if (!state.handle_error(code))
            handle_callback(state);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    for (const tx_type& tx: transactions)
    {
        ++state;
        fullnode.protocol.broadcast_transaction(tx, handler);
    }

    client.poll(state.stopped());

    return state.get_result();
}

