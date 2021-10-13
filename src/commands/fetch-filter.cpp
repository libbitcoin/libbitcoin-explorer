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

// Sponsored in part by Digital Contract Design, LLC

#include <bitcoin/explorer/commands/fetch-filter.hpp>

#include <cstddef>
#include <cstdint>
#include <csignal>
#include <future>
#include <iostream>
#include <mutex>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/core/null_deleter.hpp>
#include <bitcoin/network.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace boost;
using namespace bc::client;
using namespace bc::explorer::config;
using namespace bc::system;

console_result fetch_filter::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto height = get_height_option();
    const hash_digest& hash = get_hash_option();
    const encoding_engine encoding = get_format_option();
    const auto connection = get_connection(*this);

    obelisk_client client(connection.retries);
    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    ////// This enables json-style array formatting.
    ////const auto json = encoding == encoding_engine::json;

    auto on_done = [&state](const code& ec,
        const message::compact_filter& response)
    {
        if (!state.succeeded(ec))
            return;

        state.output(property_tree(response));
    };

    // Height is ignored if both are specified.
    // Use the null_hash as sentinel to determine whether to use height or hash.
    if (hash == null_hash)
        client.blockchain_fetch_compact_filter(on_done, neutrino_filter_type,
            height);
    else
        client.blockchain_fetch_compact_filter(on_done, neutrino_filter_type,
            hash);

    client.wait();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
