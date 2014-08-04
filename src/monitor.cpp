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
#include <sx/command/monitor.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/serializer/item.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static bool stopped;
static console_result result;

static void subscribed(const std::error_code& error, 
    const obelisk::worker_uuid& worker)
{
    if (error)
    {
        // This command only halts on failure.
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
        stopped = true;
        return;
    }

    std::cout << SX_MONITOR_WAITING << std::endl;
}

static void subscription_handler(const std::error_code& error, size_t height,
    const hash_digest& block_hash, const transaction_type& tx)
{
    if (error)
    {
        // This command only halts on failure.
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
        stopped = true;
        return;
    }

    std::cout << boost::format(SX_MONITOR_OUTPUT) % 
        item<transaction_type>(tx) % height % hex(block_hash) << std::endl;
}

console_result monitor::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    //const auto height = get_height_option();
    const stealth_prefix prefix = get_prefix_option();

    // TODO: create stealth prefix serializer and capture this.
    constexpr size_t max_prefix_bytes = sizeof(uint32_t);
    if (prefix.size() > max_prefix_bytes * byte_bits)
    {
        cerr << SX_MONITOR_PREFIX_TOO_LONG << std::endl;
        return console_result::failure;
    }

    stopped = false;
    result = console_result::okay;

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.address.subscribe(prefix, subscription_handler, subscribed);
    client.poll(stopped);

    return result;
}

