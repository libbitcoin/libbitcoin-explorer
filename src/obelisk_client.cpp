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
#include <sx/obelisk_client.hpp>

#include <stdint.h>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/command.hpp>
#include <sx/utility/utility.hpp>

namespace sx {

obelisk_client::obelisk_client(sx::command& command, const size_t threads)
    : threadpool_(threads), fullnode_(threadpool_,
    command.get_obelisk_service_setting(),
    command.get_obelisk_client_certificate_setting().generic_string(),
    command.get_obelisk_server_public_key_setting()) {}

obelisk::fullnode_interface& obelisk_client::get_fullnode()
{
    return fullnode_;
}

bc::threadpool& obelisk_client::get_threadpool()
{
    return threadpool_;
}

// Not yet unit testable (nonvirtual pool and fullnode).
void obelisk_client::detached_poll(bool& done, uint32_t period_ms)
{
    auto work = [this, &done, period_ms] { this->work(done, period_ms); };
    std::thread worker_thread(work);
    worker_thread.detach();
}

// Not yet unit testable (nonvirtual pool and fullnode).
void obelisk_client::poll(bool& done, uint32_t period_ms)
{
    work(done, period_ms);
    stop();
}

// Test wrapper, not testable.
void obelisk_client::sleep(uint32_t period_ms)
{
    sleep_ms(period_ms);
}

// Not yet unit testable (nonvirtual pool).
void obelisk_client::stop()
{
    auto& pool = get_threadpool();
    pool.stop();
    pool.join();
}

// Not yet unit testable (nonvirtual fullnode).
void obelisk_client::work(bool& done, uint32_t period_ms)
{
    auto& fullnode = get_fullnode();
    while (!done)
    {
        fullnode.update();
        sleep(period_ms);
    }
}

} // sx