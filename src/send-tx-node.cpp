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
#include <sx/command/send-tx-node.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/async_client.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static void handle_sent(callback_args& args, transaction_type& tx)
{
    args.output() << boost::format(SX_SEND_TX_NODE_OUTPUT) % transaction(tx) %
        now() << std::endl;
    args.stopped() = true;
}

static void handle_send(callback_args& args, channel_ptr node,
    transaction_type& tx)
{
    const auto sent_handler = [&args, &tx](const std::error_code& code)
    {
        handle_error(args, code);
        handle_sent(args, tx);
    };

    node->send(tx, sent_handler);
}

console_result send_tx_node::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& host = get_name_option();
    const auto& port = get_port_option();
    const auto& transactions = get_transactions_argument();

    callback_args args(error, output);
    const auto send_handler = [&args](const std::error_code& code,
        channel_ptr node, transaction_type& tx)
    {
        handle_error(args, code);
        handle_send(args, node, tx);
    };

    async_client client(*this, 4);
    auto& pool = client.get_threadpool();
    handshake shake(pool);
    network net(pool);

    for (const transaction_type& tx: transactions)
        connect(shake, net, host, port, 
            std::bind(send_handler, ph::_1, ph::_2, tx));

    client.poll(args.stopped(), 2000);

    return args.result();
}