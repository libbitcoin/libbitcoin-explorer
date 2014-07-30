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
#include <sx/command/sendtx-obelisk.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;

// TODO: this should be a member of sx::extensions::sendtx_obelisk,
// otherwise concurrent test execution will collide on shared state.
static bool node_stopped;
static console_result result;

// TODO: node_stopped should be passed here via closure
// or by converting this to a member function.
static void handle_broadcast(const std::error_code& error)
{
    // Output the 'status' regardless of result.
    std::cout << error << std::endl;
    node_stopped = true;
}

console_result sendtx_obelisk::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto file = get_file_argument();

    node_stopped = false;
    result = console_result::okay;

    // TODO: move path/stdio into serializer.
    auto filename = file.generic_string();

    transaction_type tx;
    if (!load_satoshi_item<transaction_type>(tx, filename, input))
        return console_result::failure;

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.protocol.broadcast_transaction(tx, handle_broadcast);
    client.poll(node_stopped);

    return console_result::okay;
}

