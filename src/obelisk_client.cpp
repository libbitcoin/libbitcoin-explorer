/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
// #include "precompile.hpp"
#include <bitcoin/explorer/obelisk_client.hpp>

#include <cstdint>
#include <functional>
#include <bitcoin/explorer/async_client.hpp>
#include <bitcoin/explorer/command.hpp>

namespace libbitcoin {
namespace explorer {

obelisk_client::obelisk_client(czmqpp::context& context)
 : socket_(context, ZMQ_DEALER),
    stream_(socket_),
    codec_(stream_,
        bc::client::obelisk_codec::on_update_nop,
        bc::client::obelisk_codec::on_unknown_nop,
        std::chrono::seconds(2),
        0)
{
}

int obelisk_client::connect()
{
    std::string address = "tcp://obelisk-testnet2.airbitz.co:9091";

    return socket_.connect(address);
}

bc::client::obelisk_codec& obelisk_client::get_codec()
{
    return codec_;
}

// Not yet unit testable (nonvirtual fullnode).
bool obelisk_client::resolve_callbacks()
{
    bool success = true;

    long delay = static_cast<long>(codec_.wakeup().count());
    czmqpp::poller poller;
    poller.add(stream_.get_socket());

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
            stream_.forward(codec_);

            if (codec_.outstanding_call_count() == 0)
            {
                delay = 0;
            }
        }
        else
        {
            // recompute the delay and signal the appropriate error callbacks
            // due to the timeout.
            delay = static_cast<long>(codec_.wakeup().count());
        }
    }

    return success;
}

void obelisk_client::poll_until_termination(long delay)
{
    czmqpp::poller poller;
    poller.add(stream_.get_socket());

    while (true)
    {
        poller.wait(delay);

        if (poller.terminated())
        {
            break;
        }

        if (!poller.expired())
        {
            stream_.forward(codec_);
        }
    }
}

} // namespace explorer
} // namespace libbitcoin
