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
#include <bitcoin/explorer/commands/watch-stealth.hpp>

#include <iostream>
#include <czmq++/czmqpp.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

static void handle_error(callback_state& state, const std::error_code& error)
{
    state.handle_error(error);
}

static void handle_update(callback_state& state, base2 prefix,
    const payment_address& address, size_t, const hash_digest& block_hash,
    const transaction_type& tx)
{
    state.output(prop_tree(tx, block_hash, prefix));
}

static void subscribe_from_prefix(obelisk_client& client,
    callback_state& state, base2 prefix, bool& success_indicator)
{
    auto on_done = [&state, &prefix, &success_indicator]()
    {
        if (state.get_engine() != encoding_engine::native)
            state.output(format(BX_WATCH_STEALTH_PREFIX_WAITING) % prefix);

        success_indicator = true;
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    client.get_codec().subscribe(on_error, on_done, prefix);
}

// This command only halts on failure.
console_result watch_stealth::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& prefixes = get_prefixs_argument();
    const auto& server = get_server_address_setting();

    callback_state state(error, output, encoding);

    auto on_update = [&state, &prefixes](const payment_address& address,
        size_t height, const hash_digest& block_hash, 
        const transaction_type& tx)
    {
        for (auto prefix: prefixes)
        {
            if (bc::stealth_match(prefix, address.hash().data()))
                handle_update(state, prefix, address, height, block_hash, tx);
        }
    };

    czmqpp::context context;
    obelisk_client client(context);

    if (client.connect(server) < 0)
        return console_result::failure;

    bool has_subscribed = false;
    client.get_codec().set_on_update(on_update);

    for (auto prefix: prefixes)
        subscribe_from_prefix(client, state, prefix, has_subscribed);

    // poll for subscribe callbacks
    if (client.resolve_callbacks())
    {
        // keep polling for updates if any subscriptions were established.
        if (has_subscribed)
            client.poll_until_termination();
    }

    return state.get_result();
}
