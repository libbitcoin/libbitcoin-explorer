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
#include <explorer/commands/fetch-confirmations.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <explorer/callback_state.hpp>
#include <explorer/define.hpp>
#include <explorer/obelisk_client.hpp>
#include <explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

static void handle_callback(callback_state& state, size_t position,
    const index_list& confirmations)
{
    // Why is this a list and why is it not summarized by transaction?
    for (const auto& confirmation: confirmations)
        state.output(format(BX_FETCH_CONFIRMATIONS_OUTPUT) % position %
            confirmation);

    --state;
}

console_result fetch_confirmations::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& transactions = get_transactions_argument();
    const auto& encoding = get_format_option();

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    callback_state state(error, output, encoding);

    // We avoid using the tx hash for confirmations because of malleability.
    for (const auto& tx: transactions)
    {
        const auto handler = [&state, &tx](const std::error_code& code,
            const index_list& unconfirmed)
        {
            if (!state.handle_error(code))
                handle_callback(state, state, unconfirmed);
        };

        ++state;
        fullnode.transaction_pool.validate(tx, handler);
    }

    client.poll(state.stopped());

    return state.get_result();
}