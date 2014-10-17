/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#ifndef BX_ASYNC_CLIENT_HPP
#define BX_ASYNC_CLIENT_HPP

#include <functional>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {

/**
 * Class to simplify async client usage. 
 */
class async_client
{
public:

    /**
     * The default polling period.
     */
    BCX_API static constexpr uint32_t default_poll_period_ms = 100;
    
    /**
     * The default number of threads.
     */
    BCX_API static constexpr size_t default_threadpool_size = 1;

    /**
     * Initialization constructor, establish threadpool (RAII).
     * @param[in]  command  The command being processed.
     * @param[in]  threads  The number of pool threads to initialize.
     */
    BCX_API async_client(explorer::command& command,
        const size_t threads=default_threadpool_size);

    /**
     * Destructor, kill threads (RAII).
     */
    BCX_API ~async_client();

    /**
     * Get the value of the threadpool.
     */
    BCX_API virtual threadpool& get_threadpool();

    /**
     * Poll for changes until stopped.
     * @param[in]  done       A flag that signals cessation of polling.
     * @param[in]  period_ms  The polling period in ms, defaults to 100.
     * @param[in]  action     The poll function to execute, defaults to null.
     */
    BCX_API virtual void poll(bool& done, uint32_t period_ms = default_poll_period_ms,
        std::function<void()> action=nullptr);

    /**
     * Sleep test wrapper.
     */
    BCX_API virtual void sleep(uint32_t period_ms);

    /**
     * Stop polling.
     */
    BCX_API virtual void stop();

private:

    /**
     * The threadpool of the client.
     */
    threadpool threadpool_;
};

} // namespace explorer
} // namespace libbitcoin

#endif