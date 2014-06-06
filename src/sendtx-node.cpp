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
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/command/sendtx-node.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;
using namespace sx;
using namespace sx::extensions;

// TODO: this should be a member of sx::extensions::sendtx_node,
// otherwise concurrent test execution will collide on shared state.
static bool node_stopped = false;

// TODO: node_stopped should be passed here via closure
// or by converting this to a member function.
static void send_tx(const std::error_code& ec, channel_ptr node, 
    transaction_type& tx)
{
    // There must be a better way.
    terminate_process_on_error(ec);

    std::cout << "sendtx: Sending " << hash_transaction(tx) << std::endl;
    auto handle_send =
        [node](const std::error_code& ec)
        {
            if (ec)
                log_warning() << "Send failed: " << ec.message();
            else
                std::cout << "sendtx: Sent " << time(nullptr) << std::endl;

            node_stopped = true;
        };
    node->send(tx, handle_send);
}

console_result sendtx_node::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 4))
        return console_result::failure;

    transaction_type tx;
    const auto filename(get_filename(argc, argv));
    if (!load_satoshi_item<transaction_type>(tx, filename, std::cin))
    {
        std::cerr << "sx: Deserializing transaction failed." << std::endl;
        return console_result::failure;
    }

    // TODO: read config.service option and alter default hostname accordingly?
    std::string hostname(argc > 2 ? argv[2] : "localhost");

    // TODO: read config.testnet option and alter default port accordingly?
    auto port = static_cast<uint16_t>(port_default::mainnet);

    if (argc > 3)
    {
        if (!parse<uint16_t>(argv[3], port))
        {
            std::cerr << "sendtx: Bad port number provided" << std::endl;
            return console_result::failure;
        }
    }

    threadpool pool(4);
    handshake shake(pool);
    network net(pool);
    connect(shake, net, hostname, port, 
        std::bind(send_tx, _1, _2, std::ref(tx)));
    while (!node_stopped)
        sleep_ms(2000);
    pool.stop();
    pool.join();

    return console_result::okay;
}
    
