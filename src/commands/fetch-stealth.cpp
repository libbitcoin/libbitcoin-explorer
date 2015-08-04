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

#include <bitcoin/explorer/commands/fetch-stealth.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/primitives/base2.hpp>
#include <bitcoin/explorer/primitives/stealth.hpp>
#include <bitcoin/explorer/prop_tree.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result fetch_stealth::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto height = get_height_option();
    const auto& encoding = get_format_option();
    const auto& prefix = get_prefix_argument();
    const auto connection = get_connection(*this);

    obelisk_client client(connection);

    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    if (prefix.size() > stealth_address::max_prefix_bits)
    {
        error << BX_FETCH_STEALTH_PREFIX_TOO_LONG << std::endl;
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    auto on_done = [&state, &prefix](const client::stealth_list& list)
    {
        // Write out the transaction hashes of *potential* matches.
        state.output(prop_tree(list));
    };

    auto on_error = [&state](const std::error_code& error)
    {
        state.succeeded(error);
    };

    client.get_codec()->fetch_stealth(on_error, on_done, prefix, height);
    client.resolve_callbacks();

    return state.get_result();
}
