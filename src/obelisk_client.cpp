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
#include <explorer/obelisk_client.hpp>

#include <functional>
#include <cstdint>
#include <obelisk/obelisk.hpp>
#include <explorer/async_client.hpp>
#include <explorer/command.hpp>

namespace libbitcoin {
namespace explorer {

obelisk_client::obelisk_client(bc::explorer::command& command, 
    const size_t threads)
    : async_client(command, threads), fullnode_(get_threadpool(),
    command.get_server_address_setting(),
    command.get_server_client_certificate_setting().generic_string(),
    command.get_server_server_public_key_setting())
{
}

obelisk::fullnode_interface& obelisk_client::get_fullnode()
{
    return fullnode_;
}

// Not yet unit testable (nonvirtual fullnode).
void obelisk_client::poll(bool& done, uint32_t period_ms,
    std::function<void()> action)
{
    if (action)
    {
        async_client::poll(done, period_ms, action);
        return;
    }

    auto& fullnode = get_fullnode();
    while (!done)
    {
        fullnode.update();
        sleep(period_ms);
    }
}

} // namespace explorer
} // namespace libbitcoin
