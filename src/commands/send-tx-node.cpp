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

#include <bitcoin/explorer/commands/send-tx-node.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/async_client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result send_tx_node::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& host = get_host_option();
    const auto& port = get_port_option();
    const tx_type& transaction = get_transaction_argument();

    callback_state state(error, output);

    const auto connect_handler = [&state](const std::error_code& code,
        bc::network::channel_ptr node, const tx_type& tx)
    {
        const auto send_handler = [&state, &tx](const std::error_code& code)
        {
            if (state.handle_error(code))
                state.output(format(BX_SEND_TX_OUTPUT) % now());
                
            --state;
        };

        if (state.handle_error(code))
            node->send(tx, send_handler);
    };

    async_client client(4);
    auto& pool = client.get_threadpool();
    bc::network::handshake shake(pool);
    bc::network::network net(pool);

    ++state;
    connect(shake, net, host, port,
        std::bind(connect_handler, ph::_1, ph::_2, std::ref(transaction)));

    client.poll(state.stopped(), 2000);

    return state.get_result();
}