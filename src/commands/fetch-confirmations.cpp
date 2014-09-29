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
// #include "precompile.hpp"
#include <bitcoin/explorer/commands/fetch-confirmations.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

static void handle_error(callback_state& state, const std::error_code& error)
{
    state.handle_error(error);
}

static void handle_callback(callback_state& state, size_t position,
    const index_list& confirmations)
{
    // Why is this a list and why is it not summarized by transaction?
    for (const auto& confirmation: confirmations)
        state.output(format(BX_FETCH_CONFIRMATIONS_OUTPUT) % position %
            confirmation);
}

static void fetch_confirmations_from_transaction(obelisk_client& client,
    callback_state& state, primitives::transaction transaction)
{
    auto on_done = [&state](const index_list& unconfirmed)
    {
        handle_callback(state, state, unconfirmed);
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    client.get_codec().validate(on_error, on_done, transaction);
}

console_result fetch_confirmations::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& transactions = get_transactions_argument();
    const auto& encoding = get_format_option();
    const auto& server = get_server_address_setting();

    czmqpp::context context;
    obelisk_client client(context);

    if (client.connect(server) < 0)
        return console_result::failure;

    callback_state state(error, output, encoding);

    for (auto tx: transactions)
        fetch_confirmations_from_transaction(client, state, tx);

    client.resolve_callbacks();

    return state.get_result();
}
