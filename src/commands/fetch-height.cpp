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
#include <bitcoin/explorer/commands/fetch-height.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;

static void handle_error(callback_state& state, const std::error_code& error)
{
    state.handle_error(error);
}

static void handle_callback(callback_state& state, size_t height)
{
    // all formats are valid/same/base10.
    state.output(height);
}

console_result fetch_height::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto retries = get_general_retries_setting();
    const auto timeout = get_general_wait_setting();
    const auto& server = get_server_address_setting();

    czmqpp::context context;
    obelisk_client client(context, sleep_time(timeout), retries);

    if (client.connect(server) < 0)
        return console_result::failure;

    callback_state state(error, output);

    auto on_done = [&state](size_t height)
    {
        handle_callback(state, height);
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    client.get_codec().fetch_last_height(on_error, on_done);
    client.resolve_callbacks();

    return state.get_result();
}
