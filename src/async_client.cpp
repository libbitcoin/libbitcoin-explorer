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
#include "precompile.hpp"
#include <sx/async_client.hpp>

#include <functional>
#include <stdint.h>
#include <bitcoin/bitcoin.hpp>
#include <sx/command.hpp>
#include <sx/utility/utility.hpp>

namespace sx {

async_client::async_client(sx::command& command, const size_t threads)
    : threadpool_(threads) {}

async_client::~async_client()
{
    stop();
}

bc::threadpool& async_client::get_threadpool()
{
    return threadpool_;
}

// Not yet unit testable (nonvirtual pool).
void async_client::detached_poll(bool& done, uint32_t period_ms,
    std::function<void()> action)
{
    auto work = [this, &done, period_ms, action]
    { 
        this->poll(done, period_ms, action);
    };

    std::thread worker_thread(work);
    worker_thread.detach();
}

void async_client::poll(bool& done, uint32_t period_ms,
    std::function<void()> action)
{
    while (!done)
    {
        if (action)
            action();
        sleep(period_ms);
    }
}

// Test wrapper, not testable.
void async_client::sleep(uint32_t period_ms)
{
    sleep_ms(period_ms);
}

// Not yet unit testable (nonvirtual pool).
void async_client::stop()
{
    auto& pool = get_threadpool();
    pool.stop();
    pool.join();
}

} // sx