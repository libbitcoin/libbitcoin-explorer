/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include "precompile.hpp"
#include <sx/command/watch-stealth.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/callback_state.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/prop_tree.hpp>
#include <sx/serializer/encoding.hpp>
#include <sx/serializer/base16.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace obelisk;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static void handle_subscribed(callback_state& state, const prefix& prefix,
    const worker_uuid& worker)
{
    //if (state.get_engine() != encoding::engine::native)
    state.output(format(SX_WATCH_PREFIX_WAITING) % prefix);
}

// This returns the entire transaction as opposed to just metadata!
static void handle_update(callback_state& state, const prefix& prefix,
    size_t height, const hash_digest& block_hash, const tx_type& tx)
{
    // Since this is a watcher we expose a formatter only (no base16).
    state.output(prop_tree(tx, block_hash, prefix));

    --state;
}

// This command only halts on failure.
console_result watch_stealth::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& prefixes = get_prefixs_argument();
    const auto& encoding = get_format_option();

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    callback_state state(error, output, encoding);

    for (const auto& prefix: prefixes)
    {
        const auto update_handler = [&state, &prefix](
            const std::error_code& code, size_t height, 
            const hash_digest& block_hash, const tx_type& tx)
        {
            if (!state.handle_error(code))
                handle_update(state, prefix, height, block_hash, tx);
        };

        const auto subscribed_handler = [&state, &prefix](
            const std::error_code& code, const worker_uuid& worker)
        {
            if (!state.handle_error(code))
                handle_subscribed(state, prefix, worker);
        };

        ++state;
        fullnode.address.subscribe(prefix, update_handler, subscribed_handler);
    }

    client.poll(state.stopped());

    return state.get_result();
}