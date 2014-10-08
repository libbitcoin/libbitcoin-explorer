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
#ifndef BX_OBELISK_CLIENT_HPP
#define BX_OBELISK_CLIENT_HPP

#include <czmq++/czmqpp.hpp>
#include <bitcoin/client.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {

/**
 * Class to simplify libbitcoin server usage. 
 */
class obelisk_client
{
public:

    /**
     * Initialization constructor.
     * @param[in]  context  The zmq context.
     * @param[in]  timeout  The call timeout, defaults to zero.
     * @param[in]  retries  The number of retries allowed, defaults to zero.
     */
    obelisk_client(czmqpp::context& context, 
        const client::period_ms& timeout=client::period_ms(0),
        uint8_t retries=0);

    /**
     * Connect to the specified server address.
     * @param[in]  address  The server address.
     * @return              The connection status, negative for failure.
     */
    virtual int connect(const std::string& address);

    /**
     * Get the value of the codec property.
     * @return The codec.
     */
    virtual std::shared_ptr<client::obelisk_codec> get_codec();
    
    /**
     * Resolve callback functions.
     * @return True if not terminated before completion.
     */
    virtual bool resolve_callbacks();

    /**
     * Poll the connection until the request times out or terminates.
     * @param[in]  timeout  The poll timeout, defaults to zero.
     */
    virtual void poll_until_termination(
        const client::period_ms& timeout=client::period_ms(0));

private:

    czmqpp::socket socket_;
    std::shared_ptr<client::socket_stream> stream_;
    std::shared_ptr<client::obelisk_codec> codec_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
