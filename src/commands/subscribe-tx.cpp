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

#include <bitcoin/explorer/commands/subscribe-tx.hpp>

#include <cstddef>
#include <iostream>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::client;
using namespace bc::explorer::config;

console_result subscribe_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& server_url = get_server_url_argument();
    const auto duration = get_duration_option();
    auto connection = get_connection(*this);

    if (!server_url.empty())
        connection.transaction_server = server_url;

    callback_state state(error, output, encoding);

    auto on_transaction = [&state](const chain::transaction& tx)
    {
        state.output(encode_base16(tx.hash()));
    };

    obelisk_client client(0, 0);
    if (!client.subscribe_transaction(connection.transaction_server,
        on_transaction))
    {
        output << BX_SUBSCRIBE_TX_FAILED << std::endl;
        return console_result::failure;
    }

    client.monitor(duration);
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
