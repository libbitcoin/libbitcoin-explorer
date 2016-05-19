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

#include <bitcoin/explorer/obelisk_client.hpp>

#include <chrono>
#include <cstdint>
#include <thread>
#include <boost/filesystem.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/primitives/cert_key.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::config;
using namespace bc::explorer::primitives;
using namespace bc::protocol;
using namespace std::chrono;
using boost::filesystem::path;

namespace libbitcoin {
namespace explorer {

static BC_CONSTFUNC uint32_t seconds_to_micro(uint16_t seconds)
{
    // This cannot overflow uint32.
    return seconds * 1000000;
};

static const auto on_unknown = [](const std::string&){};

// Retries is overloaded as configuration for retries as well.
obelisk_client::obelisk_client(uint16_t timeout_seconds, uint8_t retries)
  : socket_(context_, zmq::socket::role::dealer),
    authenticate_(context_),
    stream_(socket_),
    retries_(retries),
    proxy(stream_, on_unknown, seconds_to_micro(timeout_seconds), retries)
{
    BITCOIN_ASSERT((bool)socket_);
}

obelisk_client::obelisk_client(const connection_type& channel)
  : obelisk_client(channel.timeout_seconds, channel.retries)
{
}

bool obelisk_client::connect(const connection_type& channel)
{
    return connect(channel.server, channel.server_public_key,
        channel.client_private_key);
}

bool obelisk_client::connect(const endpoint& address)
{
    // Arbitrary delay between connection attempts.
    static const milliseconds delay(100);
    const auto host_address = address.to_string();

    for (auto attempt = 0; attempt < 1 + retries_; ++attempt)
    {
        if (socket_.connect(host_address))
            return true;

        std::this_thread::sleep_for(delay);
    }

    return false;
}

bool obelisk_client::connect(const endpoint& address,
    const std::string& server_public_key,
    const std::string& client_private_key)
{
    if (!server_public_key.empty())
    {
        if (!socket_.set_curve_client(server_public_key))
            return false;

        // Only apply the client key if the server key is configured.
        if (!client_private_key.empty())
        {
            // The certicate construction generates the client public key.
            if (!socket_.set_certificate({ client_private_key }))
                return false;
        }
    }

    return connect(address);
}

// Used by fetch-* commands, fires reply, unknown or error handlers.
void obelisk_client::wait()
{
    const auto socket_id = socket_.id();

    zmq::poller poller;
    poller.add(socket_);
    auto delay = refresh();

    while (!empty() && !poller.terminated() && !poller.expired() &&
        poller.wait(delay) == socket_id)
    {
        stream_.read(*this);
        delay = refresh();
    }

    // Invoke error handlers for any still pending.
    clear(error::channel_timeout);
}

// Used by watch-* commands, fires registered update or unknown handlers.
void obelisk_client::monitor(uint32_t timeout_seconds)
{
    const auto socket_id = socket_.id();
    const auto deadline = steady_clock::now() + seconds(timeout_seconds);

    zmq::poller poller;
    poller.add(socket_);
    auto delay = remaining(deadline);

    while (!poller.terminated() && !poller.expired() &&
        poller.wait(delay) == socket_id)
    {
        stream_.read(*this);
        delay = remaining(deadline);
    }
}

} // namespace explorer
} // namespace libbitcoin
