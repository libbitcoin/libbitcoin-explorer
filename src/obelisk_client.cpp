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

#include <boost/filesystem.hpp>
#include <czmq++/czmqpp.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/async_client.hpp>
#include <bitcoin/explorer/primitives/cert_key.hpp>
#include <bitcoin/explorer/primitives/uri.hpp>

using namespace bc;
using namespace bc::client;
using namespace bc::explorer::primitives;
using namespace czmqpp;
using boost::filesystem::path;

namespace libbitcoin {
namespace explorer {

constexpr int zmq_no_linger = 0;
constexpr int zmq_curve_enabled = 1;

obelisk_client::obelisk_client(const period_ms& timeout, uint8_t retries)
  : socket_(context_, ZMQ_DEALER),
    authenticate_(context_)
{
    BITCOIN_ASSERT(socket_.self() != nullptr);
    stream_ = std::make_shared<socket_stream>(socket_);
    auto base_stream = std::static_pointer_cast<message_stream>(stream_);
    codec_ = std::make_shared<obelisk_codec>(base_stream);
    codec_->set_timeout(timeout);
    codec_->set_retries(retries);
}

obelisk_client::obelisk_client(const connection_type& channel)
  : obelisk_client(channel.wait, channel.retries)
{
#ifdef _MSC_VER
    // Hack to prevent czmq from writing to stdout/stderr on Windows.
    // This will prevent authentication feedback, but also prevent crashes.
    // It is necessary to prevent stdio when using our utf8-everywhere pattern.
    // TODO: provide a FILE* here that we can direct to our own log/console.
    zsys_set_logstream(NULL);
#endif
}

bool obelisk_client::connect(const uri& address)
{
    // ZMQ *only* returns 0 or -1 for this call, so make boolean.
    const auto success = socket_.connect(address.to_string()) == zmq_success;
    if (success)
        socket_.set_linger(zmq_no_linger);

    return success;
}

bool obelisk_client::connect(const uri& address,
    const cert_key& server_public_cert)
{
    const auto server_key = server_public_cert.get_base85();

    if (!server_key.empty())
    {
        // If there is no cert loaded this uses a generated one.
        certificate_.apply(socket_);
        socket_.set_curve_serverkey(server_key);

#ifndef _MSC_VER
        // Hack to prevent czmq from writing to stdout/stderr on Windows.
        // This will prevent authentication feedback, but also prevent crashes.
        // It is necessary to prevent stdio when using our utf8-everywhere pattern.
        // TODO: modify czmq to not hardcode stdout/stderr for verbose output.
        authenticate_.set_verbose(true);
#endif
    }

    return connect(address);
}

bool obelisk_client::connect(const uri& address, 
    const cert_key& server_public_cert, const path& client_private_cert_path)
{
    const auto server_key = server_public_cert.get_base85();
    const auto cert_path = client_private_cert_path.string();

    // Only apply the client cert if the server key is configured.
    // This allows connections where neither is required, which is okay.
    if (!cert_path.empty() && !server_key.empty())
    {
        certificate_.reset(cert_path);

        if (!certificate_.valid())
            return false;

        certificate_.apply(socket_);
    }

    return connect(address, server_public_cert);
}

bool obelisk_client::connect(const connection_type& channel)
{
    return connect(channel.server, channel.key, channel.cert_path);
}

std::shared_ptr<obelisk_codec> obelisk_client::get_codec()
{
    return codec_;
}

bool obelisk_client::resolve_callbacks()
{
    auto delay = static_cast<int>(codec_->wakeup().count());
    czmqpp::poller poller;
    poller.add(stream_->get_socket());

    while (delay > 0)
    {
        poller.wait(delay);

        if (poller.terminated())
            return false;

        if (poller.expired())
        {
            // recompute the delay and signal the appropriate error callbacks.
            delay = static_cast<int>(codec_->wakeup().count());
            continue;
        }

        stream_->signal_response(codec_);
        if (codec_->outstanding_call_count() == 0)
            break;
    }

    return true;
}

void obelisk_client::poll_until_termination(const client::period_ms& timeout)
{
    czmqpp::poller poller;
    poller.add(stream_->get_socket());

    while (true)
    {
        poller.wait(static_cast<int>(timeout.count()));

        if (poller.terminated())
            break;

        if (!poller.expired())
            stream_->signal_response(codec_);
    }
}

void obelisk_client::poll_until_timeout_cumulative(const period_ms& timeout)
{
    czmqpp::poller poller;
    poller.add(stream_->get_socket());

    // calculate expected expiration time
    auto expiry = std::chrono::steady_clock::now() + timeout;

    while (std::chrono::steady_clock::now() < expiry)
    {
        // calculate maximum interval from now to expiration
        auto max_wait_interval = std::chrono::duration_cast<period_ms>(
            expiry - std::chrono::steady_clock::now());

        poller.wait(static_cast<int>(max_wait_interval.count()));

        if (poller.terminated())
            break;

        if (!poller.expired())
            stream_->signal_response(codec_);
    }
}

} // namespace explorer
} // namespace libbitcoin
