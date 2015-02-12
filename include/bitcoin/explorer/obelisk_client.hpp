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

#include <boost/filesystem.hpp>
#include <czmq++/czmqpp.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/cert_key.hpp>
#include <bitcoin/explorer/primitives/uri.hpp>
#include <bitcoin/explorer/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {

/**
 * The standard libzmq success code.
 */
constexpr int zmq_success = 0;

/**
 * Class to simplify obelisk/libbitcoin-server usage. 
 * This class hides *all* use of czmqpp/czmq/zmq/libsodium.
 */
class obelisk_client
{
public:
    /**
     * Initialization constructor.
     * @param[in]  timeout  The call timeout, defaults to zero (instant).
     * @param[in]  retries  The number of retries allowed, defaults to zero.
     */
    BCX_API obelisk_client(
        const client::period_ms& timeout=client::period_ms(0),
        uint8_t retries=0);

    /**
     * Initialization constructor.
     * @param[in]  channel  The channel to initialize.
     */
    BCX_API obelisk_client::obelisk_client(const connection_type& channel);

    /**
     * Connect to the specified server address.
     * @param[in]  address              The server address.
     * @return                          True if connected, otherwise false.
     */
    BCX_API virtual bool connect(const primitives::uri& address);

    /**
     * Connect to the specified server address.
     * @param[in]  address              The server address.
     * @param[in]  server_public_cert   The server public certificate key.
     * @return                          True if connected, otherwise false.
     */
    BCX_API virtual bool connect(const primitives::uri& address,
        const primitives::cert_key& server_public_cert);

    /**
     * Connect to the specified server address.
     * @param[in]  address                   The server address.
     * @param[in]  server_public_cert        The server public certificate key.
     * @param[in]  client_private_cert_path  The client private cert file path.
     * @return                               True if connected, otherwise false.
     */
    BCX_API virtual bool connect(const primitives::uri& address,
        const primitives::cert_key& server_public_cert,
        const boost::filesystem::path& client_private_cert_path);

    /**
     * Connect using the specified server channel.
     * @param[in]  channel  The channel to connect.
     * @return              True if connected, otherwise false.
     */
    BCX_API virtual bool connect(const connection_type& channel);

    /**
     * Get the value of the codec property.
     * @return The codec.
     */
    BCX_API virtual std::shared_ptr<client::obelisk_codec> get_codec();
    
    /**
     * Resolve callback functions.
     * @return True if not terminated before completion.
     */
    BCX_API virtual bool resolve_callbacks();

    /**
     * Poll the connection until the request terminates.
     * @param[in]  timeout  The poll timeout, defaults to zero.
     */
    BCX_API virtual void poll_until_termination(
        const client::period_ms& timeout=client::period_ms(0));

    /**
     * Poll the connection until the request times out or terminates.
     * @param[in]  timeout  The poll timeout, defaults to zero.
     */
    BCX_API virtual void poll_until_timeout_cumulative(
        const client::period_ms& timeout=client::period_ms(0));

private:

    czmqpp::context context_;
    czmqpp::socket socket_;
    std::shared_ptr<client::socket_stream> stream_;
    std::shared_ptr<client::obelisk_codec> codec_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
