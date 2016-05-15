/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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

#include <cstdint>
#include <boost/filesystem.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/cert_key.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {

static BC_CONSTEXPR int zmq_success = 0;

/// This class hides all libbitcoin-protocol.
/// Class to simplify obelisk/libbitcoin-server usage. 
class BCX_API obelisk_client
  : public client::proxy
{
public:
    obelisk_client(const connection_type& channel);
    obelisk_client(uint16_t timeout_seconds, uint8_t retries);

    virtual bool connect(const config::endpoint& address);

    virtual bool connect(const config::endpoint& address,
        const primitives::cert_key& server_public_cert);

    virtual bool connect(const config::endpoint& address,
        const primitives::cert_key& server_public_cert,
        const boost::filesystem::path& client_private_cert_path);

    virtual bool connect(const connection_type& channel);

    // Wait for server to respond, until timeout.
    void wait();

    // Monitor for subscription notifications, until timeout.
    void monitor(uint32_t timeout_seconds);

private:
    protocol::zmq::context context_;
    protocol::zmq::socket socket_;
    protocol::zmq::certificate certificate_;
    protocol::zmq::authenticator authenticate_;
    client::socket_stream stream_;
    const uint8_t retries_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
