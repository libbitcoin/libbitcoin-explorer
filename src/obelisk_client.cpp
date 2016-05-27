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

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <thread>
#include <boost/filesystem.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/config/cert_key.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::config;
using namespace bc::explorer::config;
using namespace bc::protocol;
using namespace std::chrono;
using boost::filesystem::path;

namespace libbitcoin {
namespace explorer {

static uint32_t to_milliseconds(uint16_t seconds)
{
    const auto milliseconds = static_cast<uint32_t>(seconds) * 1000;
    return std::min(milliseconds, max_uint32);
};

static const auto on_unknown = [](const std::string&){};

// Retries is overloaded as configuration for retries as well.
obelisk_client::obelisk_client(uint16_t timeout_seconds, uint8_t retries)
  : socket_(context_, zmq::socket::role::dealer),
    stream_(socket_),
    retries_(retries),
    proxy(stream_, on_unknown, to_milliseconds(timeout_seconds), retries)
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
    const auto host_address = address.to_string();

    for (auto attempt = 0; attempt < 1 + retries_; ++attempt)
    {
        if (socket_.connect(host_address))
            return true;

        // Arbitrary delay between connection attempts.
        std::this_thread::sleep_for(milliseconds(100));
    }

    return false;
}

bool obelisk_client::connect(const endpoint& address,
    const sodium& server_public_key, const sodium& client_private_key)
{
    // Only apply the client (and server) key if server key is configured.
    if (server_public_key)
    {
        if (!socket_.set_curve_client(server_public_key))
            return false;

        // Generates arbitrary client keys if private key is not configured.
        if (!socket_.set_certificate({ client_private_key }))
            return false;
    }

    return connect(address);
}

// Used by fetch-* commands, fires reply, unknown or error handlers.
void obelisk_client::wait()
{
    zmq::poller poller;
    poller.add(socket_);
    auto delay = refresh();

    while (!empty() && !poller.terminated() && !poller.expired() &&
        poller.wait(delay) == socket_.id())
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
    const auto deadline = steady_clock::now() + seconds(timeout_seconds);

    zmq::poller poller;
    poller.add(socket_);
    auto delay = remaining(deadline);

    while (!poller.terminated() && !poller.expired() &&
        poller.wait(delay) == socket_.id())
    {
        stream_.read(*this);
        delay = remaining(deadline);
    }
}

} // namespace explorer
} // namespace libbitcoin
