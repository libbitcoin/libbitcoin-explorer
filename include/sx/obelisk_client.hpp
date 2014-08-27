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

#include <functional>
#include <cstdint>
#include <obelisk/obelisk.hpp>
#include <sx/async_client.hpp>
#include <sx/command.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace explorer {

/**
 * Class to simplify obelisk client usage. 
 */
class obelisk_client
    : public async_client
{
public:

    /**
     * Initialization constructor.
     * @param[in]  command  The command being processed.
     * @param[in]  threads  The number of pool threads to initialize.
     */
    obelisk_client(explorer::command& command,
        const size_t threads=default_threadpool_size);

    /**
     * Get the value of the obelisk fullnode interface.
     */
    virtual obelisk::fullnode_interface& get_fullnode();

    /**
     * Poll for changes until stopped.
     * @param[in]  done       A flag that signals cessation of polling.
     * @param[in]  period_ms  The polling period in ms, defaults to 100.
     * @param[in]  action     The poll function to execute, defaults to null.
     */
    virtual void poll(bool& done, uint32_t period_ms=default_poll_period_ms,
        std::function<void()> action=nullptr);

private:

    /**
     * Encapsulated full node client instance.
     */
    obelisk::fullnode_interface fullnode_;
};

} // explorer

#endif