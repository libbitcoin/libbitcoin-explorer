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

static constexpr uint8_t resends = 0;
static BC_CONSTFUNC uint32_t sec_to_ms(uint32_t seconds)
{
    return seconds * 1000;
};

static const auto on_unknown = [](const std::string&){};

obelisk_client::obelisk_client(uint16_t timeout_seconds, uint8_t retries)
  : socket_(context_, ZMQ_DEALER),
    authenticate_(context_),
    stream_(socket_),
    retries_(retries),
    proxy(stream_, on_unknown, sec_to_ms(timeout_seconds), resends)
{
    BITCOIN_ASSERT(socket_.self() != nullptr);
}

obelisk_client::obelisk_client(const connection_type& channel)
  : obelisk_client(channel.timeout_seconds, channel.retries)
{
}

bool obelisk_client::connect(const connection_type& channel)
{
    return connect(channel.server, channel.key, channel.cert_path);
}

bool obelisk_client::connect(const endpoint& address)
{
    // Arbitrary delay between connection attempts.
    static const milliseconds delay(100);
    const auto host_address = address.to_string();

    for (auto attempt = 0; attempt < 1 + retries_; ++attempt)
    {
        if (socket_.connect(host_address) == zmq_success)
            return true;

        std::this_thread::sleep_for(delay);
    }

    return false;
}

bool obelisk_client::connect(const endpoint& address,
    const cert_key& server_public_cert)
{
    const auto server_key = server_public_cert.get_base85();

    if (!server_key.empty())
    {
        // If there is no cert loaded this uses a generated one.
        certificate_.apply(socket_);
        socket_.set_curve_serverkey(server_key);

        // TODO: make configurable.
        authenticate_.set_verbose(true);
    }

    return connect(address);
}

bool obelisk_client::connect(const endpoint& address,
    const cert_key& server_public_cert, const path& client_private_cert_path)
{
    const auto server_key = server_public_cert.get_base85();
    const auto cert_path = client_private_cert_path.string();

    // Only apply the client cert if the server key is configured.
    // This allows connections where neither is required, which is okay.
    if (!cert_path.empty() && !server_key.empty())
    {
        certificate_.reset(cert_path);

        if (!certificate_)
            return false;

        certificate_.apply(socket_);
    }

    return connect(address, server_public_cert);
}

// Used by fetch-* commands, fires reply, unknown or error handlers.
void obelisk_client::wait()
{
    zmq::poller poller(socket_);
    auto remainder_ms = refresh();

    while (!empty() && !poller.terminated() && !poller.expired() &&
        poller.wait(remainder_ms) == socket_)
    {
        stream_.read(*this);
        remainder_ms = refresh();
    }

    // Invoke error handlers for any still pending.
    clear(error::channel_timeout);
}

// Used by watch-* commands, fires registered update or unknown handlers.
void obelisk_client::monitor(uint32_t timeout_seconds)
{
    zmq::poller poller(socket_);
    const auto deadline = steady_clock::now() + seconds(timeout_seconds);
    auto remainder_ms = remaining(deadline);

    while (!poller.terminated() && !poller.expired() &&
        poller.wait(remainder_ms) == socket_)
    {
        stream_.read(*this);
        remainder_ms = remaining(deadline);
    }
}

} // namespace explorer
} // namespace libbitcoin
