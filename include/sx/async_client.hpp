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
#ifndef SX_ASYNC_CLIENT_HPP
#define SX_ASYNC_CLIENT_HPP

#include <functional>
#include <stdint.h>
#include <bitcoin/bitcoin.hpp>
#include <sx/command.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

/**
 * Class to simplify async client usage. 
 */
class async_client
{
public:

    /**
     * The default polling period.
     */
    static constexpr uint32_t default_poll_period_ms = 100;
    
    /**
     * The default number of threads.
     */
    static constexpr size_t default_threadpool_size = 1;

    /**
     * Initialization constructor.
     * 
     * @param[in]  command  The command being processed.
     * @param[in]  threads  The number of pool threads to initialize.
     */
    async_client(sx::command& command,
        const size_t threads=default_threadpool_size);

    /**
     * Destructor, kill threads.
     */
    ~async_client();

    /**
     * Get the value of the threadpool.
     */
    virtual bc::threadpool& get_threadpool();

    /**
     * Poll for changes on other thread(s) until stopped.
     *
     * @param[in]  done       A flag that signals cessation of polling.
     * @param[in]  period_ms  The polling period in md, defaults to 100.
     * @param[in]  action     The poll function to execute, defaults to null.
     */
    virtual void detached_poll(bool& done,
        uint32_t period_ms=default_poll_period_ms,
        std::function<void()> action=nullptr);

    /**
     * Poll for changes until stopped.
     *
     * @param[in]  done       A flag that signals cessation of polling.
     * @param[in]  period_ms  The polling period in ms, defaults to 100.
     * @param[in]  action     The poll function to execute, defaults to null.
     */
    virtual void poll(bool& done, uint32_t period_ms=default_poll_period_ms,
        std::function<void()> action=nullptr);

    /**
     * Sleep test wrapper.
     */
    virtual void sleep(uint32_t period_ms);

    /**
     * Stop polling.
     */
    virtual void stop();

private:

    /**
     * The threadpool of the client.
     */
    bc::threadpool threadpool_;
};

} // sx

#endif