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

#include <bitcoin/explorer/commands/fetch-public-key.hpp>

#include <iostream>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result fetch_public_key::invoke(std::ostream& output, std::ostream& error)
{
    //// Bound parameters.
    //const auto& address = get_payment_address_argument();
    //const auto retries = get_general_retries_setting();
    //const auto timeout = get_general_wait_setting();
    //const auto& server = get_general_network_setting() == BX_TESTNET ?
    //    get_testnet_url_setting() : get_mainnet_url_setting());

    //czmqpp::context context;
    //obelisk_client client(context, period_ms(timeout), retries);

    //if (client.connect(server))
    //{
    //    display_connection_failure(error, server);
    //    return console_result::failure;
    //}

    //callback_state state(error, output);

    //auto on_done = [&state, &address](const client::history_list& rows)
    //{
    //    // TODO: get first rows tx where it (spend.hash) is not null.
    //    // TODO: convert tx to pubkey and then stop.
    //};

    //auto on_error = [&state](const std::error_code& error)
    //{
    //    state.succeeded(error);
    //};

    //client.get_codec()->address_fetch_history(on_error, on_done, address);
    //client.resolve_callbacks();

    //return state.get_result();

    error << BX_FETCH_PUBLIC_KEY_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}
