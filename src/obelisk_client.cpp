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

#include <bitcoin/explorer/obelisk_client.hpp>

#include <bitcoin/explorer/async_client.hpp>
#include <bitcoin/explorer/command.hpp>

using namespace bc::client;

namespace libbitcoin {
namespace explorer {

obelisk_client::obelisk_client(czmqpp::context& context, 
    const period_ms& timeout, uint8_t retries)
  : socket_(context, ZMQ_DEALER)
{
    stream_ = std::make_shared<socket_stream>(socket_);

    std::shared_ptr<message_stream> base_stream
        = std::static_pointer_cast<message_stream>(stream_);

    codec_ = std::make_shared<obelisk_codec>(base_stream);
    codec_->set_timeout(timeout);
    codec_->set_retries(retries);
}

int obelisk_client::connect(const std::string& address,
        const std::string& certificate_filename,
        const std::string& server_public_key)
{
    int result = (server_public_key.empty() && certificate_filename.empty()) ? 0 : -1;

    if (!server_public_key.empty() && !certificate_filename.empty())
    {
        certificate_.reset(czmqpp::load_cert(certificate_filename));
        certificate_.apply(socket_);
        socket_.set_curve_serverkey(server_public_key);
        result = 0;
    }

    if (result >= 0)
    {
        result = socket_.connect(address);
    }

    if (result >= 0)
    {
        socket_.set_linger(0);
    }

    return result;
}

std::shared_ptr<obelisk_codec> obelisk_client::get_codec()
{
    return codec_;
}

bool obelisk_client::resolve_callbacks()
{
    bool success = true;

    auto delay = static_cast<int>(codec_->wakeup().count());
    czmqpp::poller poller;
    poller.add(stream_->get_socket());

    while (delay > 0)
    {
        poller.wait(delay);

        if (poller.terminated())
        {
            success = false;
            break;
        }

        if (!poller.expired())
        {
            stream_->signal_response(codec_);

            if (codec_->outstanding_call_count() == 0)
            {
                delay = 0;
            }
        }
        else
        {
            // recompute the delay and signal the appropriate error callbacks
            // due to the timeout.
            delay = static_cast<int>(codec_->wakeup().count());
        }
    }

    return success;
}

void obelisk_client::poll_until_termination(const client::period_ms& timeout)
{
    czmqpp::poller poller;
    poller.add(stream_->get_socket());

    while (true)
    {
        poller.wait(static_cast<int>(timeout.count()));

        if (poller.terminated())
        {
            break;
        }

        if (!poller.expired())
        {
            stream_->signal_response(codec_);
        }
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
        {
            break;
        }

        if (!poller.expired())
        {
            stream_->signal_response(codec_);
        }
    }
}

} // namespace explorer
} // namespace libbitcoin
