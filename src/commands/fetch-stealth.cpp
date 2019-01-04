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

#include <bitcoin/explorer/commands/fetch-stealth.hpp>

#include <iostream>
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
using namespace bc::system::wallet;

console_result fetch_stealth::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto height = get_height_option();
    const auto& encoding = get_format_option();
    const auto& filter = get_filter_argument();
    const auto connection = get_connection(*this);

    if (filter.size() < stealth_address::min_filter_bits)
    {
        error << BX_FETCH_STEALTH_FILTER_TOO_SHORT << std::endl;
        return console_result::failure;
    }

    if (filter.size() > stealth_address::max_filter_bits)
    {
        error << BX_FETCH_STEALTH_PREFIX_TOO_LONG << std::endl;
        return console_result::failure;
    }

    obelisk_client client(connection.retries);
    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    // This enables json-style array formatting.
    const auto json = encoding == encoding_engine::json;

    auto on_done = [&state, &filter, json](const code& ec,
        const stealth::list& list)
    {
        if (!state.succeeded(ec))
            return;

        // Write out the transaction hashes of *potential* matches.
        state.output(prop_tree(list, json));
    };

    client.blockchain_fetch_stealth2(on_done, filter, height);
    client.wait();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
