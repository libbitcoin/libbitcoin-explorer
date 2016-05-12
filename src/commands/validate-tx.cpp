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

#include <bitcoin/explorer/commands/validate-tx.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result validate_tx::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& transaction = get_transaction_argument();
    const auto connection = get_connection(*this);

    obelisk_client client(connection);

    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output);

    auto on_done = [&state](const chain::point::indexes& indexes)
    {
        if (indexes.empty())
        {
            state.output(BX_VALIDATE_TX_VALID);
            return;
        }

        const auto unconfirmed = join(numbers_to_strings(indexes), ", ");
        state.output(format(BX_VALIDATE_TX_UNCONFIRMED_INPUTS) % unconfirmed);
    };

    auto on_error = [&state](const code& error)
    {
        // BX_VALIDATE_TX_INVALID_INPUT is not currently utilized.
        // The client suppresses an index list which may have 0 or one element.
        // The list contains the index of the input which caused the failure.
        state.succeeded(error);
    };

    client.transaction_pool_validate(on_error, on_done, transaction);
    client.wait();

    return state.get_result();
}
