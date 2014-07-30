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
#ifndef SX_OBELISK_CLIENT_HPP
#define SX_OBELISK_CLIENT_HPP

#include <stdint.h>
#include <thread>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/command.hpp>
#include <sx/utility/config.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

/**
 * Class to simplify obelisk client usage. 
 */
class obelisk_client
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
    obelisk_client(sx::command& command,
        const size_t threads=default_threadpool_size);

    /**
     * Destructor, calls stop.
     */
    ~obelisk_client();

    /**
     * Get the value of the obelisk fullnode interface.
     */
    virtual obelisk::fullnode_interface& get_fullnode();

    /**
     * Get the value of the threadpool.
     */
    virtual bc::threadpool& get_threadpool();

    /**
     * Poll obelisk for changes on other thread(s) until stopped.
     *
     * @param[in]  done       A flag that signals cessation of polling.
     * @param[in]  period_ms  The polling period in md, defaults to 100.
     */
    virtual void detached_poll(bool& done,
        uint32_t period_ms=default_poll_period_ms);

    /**
     * Poll obelisk for changes until stopped.
     *
     * @param[in]  done       A flag that signals cessation of polling.
     * @param[in]  period_ms  The polling period in md, defaults to 100.
     */
    virtual void poll(bool& done, uint32_t period_ms=default_poll_period_ms);

    /**
     * Sleep test wrapper.
     */
    virtual void sleep(uint32_t period_ms);

    /**
     * Stop obelisk polling.
     */
    virtual void stop();

    /**
     * Polling work.
     */
    virtual void work(bool& done, uint32_t period_ms);

private:

    /**
     * The threadpool of the obelisk client.
     * This must be declared here before fullnode_.
     */
    bc::threadpool threadpool_;

    /**
     * Type to simplify obelisk client setup.
     */
    obelisk::fullnode_interface fullnode_;
};

} // sx

#endif