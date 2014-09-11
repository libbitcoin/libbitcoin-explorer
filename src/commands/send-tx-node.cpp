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
#include "precompile.hpp"
#include <bitcoin/explorer/commands/send-tx-node.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/async_client.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

static void handle_sent(callback_state& state, tx_type& tx)
{
    state.output(format(BX_SEND_TX_NODE_OUTPUT) % transaction(tx) % now());
    --state;
}

static void handle_send(callback_state& state, channel_ptr node,
    tx_type& tx)
{
    const auto sent_handler = [&state, &tx](const std::error_code& code)
    {
        if (!state.handle_error(code))
            handle_sent(state, tx);
    };

    node->send(tx, sent_handler);
}

console_result send_tx_node::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& host = get_name_option();
    const auto& port = get_port_option();
    const auto& transactions = get_transactions_argument();

    callback_state state(error, output);
    const auto send_handler = [&state](const std::error_code& code,
        channel_ptr node, tx_type& tx)
    {
        if (!state.handle_error(code))
            handle_send(state, node, tx);
    };

    async_client client(*this, 4);
    auto& pool = client.get_threadpool();
    handshake shake(pool);
    network net(pool);

    for (const tx_type& tx: transactions)
    {
        ++state;
        connect(shake, net, host, port,
            std::bind(send_handler, ph::_1, ph::_2, tx));
    }

    client.poll(state.stopped(), 2000);

    return state.get_result();
}