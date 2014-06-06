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
#ifndef SX_CLIENT_HPP
#define SX_CLIENT_HPP

#include <sx/utility/config.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>

/* NOTE: don't declare 'using namespace foo' in heders. */

namespace sx {
    
/**
 * The default number of threads initialized by OBELISK_FULLNODE.
 */
const size_t default_threadpool_size = 1;

/**
 * The default polling period initialized by OBELISK_FULLNODE.
 */
const uint32_t default_poll_period_ms = 100;

/**
 * This prevents code repetition while retaining stack-based allocation.
 * A single thread is allocated in the pool and service settings are loaded
 * from config.
 */
#define OBELISK_FULLNODE(__pool__, __fullnode__) \
    config_map_type __config__; \
    get_config(__config__); \
    threadpool __pool__(default_threadpool_size); \
    obelisk::fullnode_interface __fullnode__( \
        __pool__, \
        __config__[SX_SETTING_SERVICE], \
        __config__[SX_SETTING_CLIENT_CERTIFICATE], \
        __config__[SX_SETTING_SERVER_PUBLIC_KEY])

/**
 * Poll obelisk for changes until stopped.
 *
 * @param[in]  fullnode   An instance of the obelisk full node interface.
 * @param[in]  pool       The threadpool used by fullnode to poll.
 * @param[in]  stopped    A flag that signals cessation of polling.
 * @param[in]  period_ms  The polling period in milliseconds, defaults to 100.
 */
void poll(obelisk::fullnode_interface& fullnode, bc::threadpool& pool,
    bool& stopped, uint32_t period_ms=default_poll_period_ms);

} // sx

#endif