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
#include <sx/command/sendtx-node.hpp>

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

// TODO: this should be a member of sx::extensions::sendtx_node,
// otherwise concurrent test execution will collide on shared state.
static bool node_stopped;
static console_result result;

// TODO: node_stopped should be passed here via closure
// or by converting this to a member function.
static void send_tx(const std::error_code& error, channel_ptr node,
    transaction_type& tx)
{
    if (error)
    {
        std::cerr << error << std::endl;
        result = console_result::failure;
        node_stopped = true;
        return;
    }

    auto handle_send = [node, tx](const std::error_code& error)
    {
        if (error)
            std::cerr << error << std::endl;
        else
        {
            const auto& hash = item<bc::transaction_type>(tx);
            std::cout << boost::format(SX_SENDTX_NODE_OUTPUT) % hash % now() 
                << std::endl;
        }

        node_stopped = true;
    };

    node->send(tx, handle_send);
}

console_result sendtx_node::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto host = get_name_option();
    const auto port = get_port_option();
    const auto& transactions = get_transactions_argument();

    // TODO: remove this hack which requires one element.
    const bc::transaction_type& tx = transactions.front();

    node_stopped = false;
    result = console_result::okay;

    // Is 4 threads and a 2 sec wait necessary here?
    async_client client(*this, 4);
    handshake shake(client.get_threadpool());
    network net(client.get_threadpool());
    connect(shake, net, host, port, std::bind(send_tx, ph::_1, ph::_2, tx));
    client.poll(node_stopped, 2000);

    return result;
}