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
#include <sx/command/fetch-height.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/utility/callback_state.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;

static void handle_callback(callback_state& state, size_t height)
{
    state.output(format("%1%") % height);
    state.stop();
}

console_result fetch_height::invoke(std::ostream& output, std::ostream& error)
{
    callback_state state(error, output);
    const auto handler = [&state](const std::error_code& code, size_t height)
    {
        if (!handle_error(state, code))
            handle_callback(state, height);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    state.start();
    fullnode.blockchain.fetch_last_height(handler);
    client.poll(state.stopped());

    return state.get_result();
}

