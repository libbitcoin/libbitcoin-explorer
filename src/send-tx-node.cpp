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
#include <sx/serializer/item.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static bool stopped;
static console_result result;

static void tx_send(const std::error_code& error, channel_ptr node,
    transaction_type& tx)
{
    if (error)
    {
        std::cerr << error << std::endl;
        result = console_result::failure;
        stopped = true;
        return;
    }

    auto handle_send = [node, tx](const std::error_code& error)
    {
        if (error)
        {
            std::cerr << error << std::endl;
            result = console_result::failure;
        }
        else
            std::cout << boost::format(SX_SEND_TX_NODE_OUTPUT) %
                item<bc::transaction_type>(tx) % now() << std::endl;

        stopped = true;
    };

    node->send(tx, handle_send);
}

console_result send_tx_node::invoke(std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto host = get_name_option();
    const auto port = get_port_option();
    const auto& transactions = get_transactions_argument();
    HANDLE_MULTIPLE_NOT_IMPLEMENTED(transactions);
    const transaction_type& tx = transactions.front();

    stopped = false;
    result = console_result::okay;

    async_client client(*this, 4);
    auto& pool = client.get_threadpool();
    handshake shake(pool);
    network net(pool);
    connect(shake, net, host, port, std::bind(tx_send, ph::_1, ph::_2, tx));
    client.poll(stopped, 2000);

    return result;
}