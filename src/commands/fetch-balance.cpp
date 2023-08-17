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

#include <bitcoin/explorer/commands/fetch-balance.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::client;
using namespace bc::explorer::config;
using namespace bc::system;
using namespace bc::system::chain;
using namespace bc::system::config;

console_result fetch_balance::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const encoding_engine  encoding = get_format_option();
    const hash_digest& key = get_hash_argument();
    const auto connection = get_connection(*this);

    if (key == null_hash)
    {
        error << BX_FETCH_BALANCE_INVALID_ARGUMENTS << std::endl;
        return console_result::failure;
    }

    obelisk_client client(connection.retries);
    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    auto on_done = [&state, &key](const code& ec, const history::list& rows)
    {
        if (!state.succeeded(ec))
            return;

        // This override summarizes the history response as balance.
        state.output(prop_tree(rows, key));
    };

    client.blockchain_fetch_history4(on_done, key);
    client.wait();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
