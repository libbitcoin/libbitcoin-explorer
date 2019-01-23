/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
    const auto& encoding = get_format_option();
    const hash_digest& hash = get_hash_option();
    const auto& address = get_payment_address_option();
    const auto connection = get_connection(*this);

    obelisk_client client(connection.retries);
    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    auto on_done = [&state, &hash, &address](const code& ec,
        const history::list& rows)
    {
        if (!state.succeeded(ec))
            return;

        // This override summarizes the history response as balance.
        if (hash == null_hash)
            state.output(prop_tree(rows, address));
        else
            state.output(prop_tree(rows, hash));
    };

    // Address is ignored if both are specified.
    // Use the null_hash as sentinel to determine whether to use address or hash.
    // This does not include unconfirmed transactions.
    if (hash == null_hash)
    {
        client.blockchain_fetch_history4(on_done, address);
    }
    else
    {
        // If a hash option is provided directly, it's been reversed already and
        // needs to be undone.
        auto reversed_hash = hash;
        std::reverse(reversed_hash.begin(), reversed_hash.end());

        client.blockchain_fetch_history4(on_done, reversed_hash);
    }

    client.wait();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
