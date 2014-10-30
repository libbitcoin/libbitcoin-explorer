/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/watch-address.hpp>

#include <iostream>
#include <czmq++/czmqpp.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/primitives/address.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

static void handle_signal(int signal)
{
    // Can't pass args using lambda capture for a simple function pointer.
    // This means there's no way to terminate without using a global variable
    // or process termination. Since the variable would screw with testing all 
    // other methods we opt for process termination here.
    exit(console_result::failure);
}

static void handle_error(callback_state& state, const std::error_code& error)
{
    state.handle_error(error);
}

static void handle_update(callback_state& state,
    const address& bitcoin_address, size_t, const hash_digest& block_hash,
    const transaction_type& tx)
{
    state.output(prop_tree(tx, block_hash, bitcoin_address));
}

static void subscribe_from_address(obelisk_client& client,
    callback_state& state, const address& bitcoin_address,
    bool& subscribed)
{
    // Do not pass the address by reference here.
    auto on_done = [&state, bitcoin_address, &subscribed]()
    {
        state.output(format(BX_WATCH_ADDRESS_ADDRESS_WAITING) % 
            bitcoin_address);

        subscribed = true;
    };

    auto on_error = [&state](const std::error_code& error)
    {
        handle_error(state, error);
    };

    client.get_codec()->subscribe(on_error, on_done, bitcoin_address);
}

// This command only halts on failure.
console_result watch_address::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto retries = get_general_retries_setting();
    const auto timeout = get_general_wait_setting();
    const auto& encoding = get_format_option();
    const auto& bitcoin_address = get_bitcoin_address_argument();
    const auto& server = if_else(get_general_network_setting() == "testnet",
        get_testnet_url_setting(), get_mainnet_url_setting());

    callback_state state(error, output, encoding);

    // Do not pass the prefixes by reference here.
    auto on_update = [&state](const address& bitcoin_address, size_t height, 
        const hash_digest& block_hash, const transaction_type& tx)
    {
        handle_update(state, bitcoin_address, height, block_hash, tx);
    };

    czmqpp::context context;
    obelisk_client client(context, period_ms(timeout), retries);

    if (client.connect(server) < 0)
        return console_result::failure;

    client.get_codec()->set_on_update(on_update);

    bool subscribed = false;

    subscribe_from_address(client, state, bitcoin_address, subscribed);

    // Catch C signals for stopping the program.
    signal(SIGABRT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    // poll for subscribe callbacks if any subscriptions were established.
    if (client.resolve_callbacks() && subscribed)
        client.poll_until_termination();

    return state.get_result();
}
