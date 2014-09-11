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
#include <bitcoin/explorer/commands/fetch-height.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/server_client.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer;
using namespace bc::explorer::commands;

//static void fetch_height_error(callback_state& state, const std::error_code& code)
//{
//    state.handle_error(code);
//}
//
//static void fetch_height_done(callback_state& state, size_t height)
//{
//    state.output(height);
//    state.stop();
//}

console_result fetch_height::invoke(std::ostream& output, std::ostream& error)
{
    //auto& address = get_server_address_setting();

    //callback_state state(error, output);
    //auto on_done = [&state](size_t height) 
    //{
    //    fetch_height_done(state, height);
    //};
    //auto on_error = [&state](const std::error_code& error)
    //{
    //    fetch_height_error(state, error);
    //};

    //zmq::context_t context;
    //client::zeromq_socket socket(context);
    //if (!socket.connect(address))
    //{
    //    // TODO: format a connection error.
    //    std::cout << "fail" << std::endl;
    //    return console_result::failure;
    //}

    //client::obelisk_codec codec(socket, obelisk_codec::on_update_nop,
    //    obelisk_codec::on_unknown_nop, std::chrono::seconds(5));

    //state.start();
    //codec.fetch_last_height(on_error, on_done);

    //while (true)
    //{
    //    auto poll_item = socket.pollitem();
    //    auto next_wakeup = codec.wakeup();
    //    auto count = next_wakeup.count();

    //    if (count == 0)
    //        break;

    //    zmq::poll(&poll_item, 1, static_cast<long>(count));
    //    if (poll_item.revents)
    //        socket.forward(codec);
    //}

    //return state.get_result();

    return console_result::failure;
}

//console_result fetch_height::invoke(std::ostream& output, std::ostream& error)
//{
//    callback_state state(error, output);
//    const auto handler = [&state](const std::error_code& code, size_t height)
//    {
//        if (!state.handle_error(code))
//            handle_callback(state, height);
//    };
//
//    server_client client(*this);
//    auto& fullnode = client.get_fullnode();
//    state.start();
//    fullnode.blockchain.fetch_last_height(handler);
//    client.poll(state.stopped());
//
//    return state.get_result();
//}
