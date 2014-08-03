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
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace obelisk;
using namespace sx;
using namespace sx::extension;

// TODO: this should be a member of sx::extensions::monitor,
// otherwise concurrent test execution will collide on shared state.
static bool stopped;
static console_result result;

// TODO: stopped should be passed here via closure
// or by converting this to a member function.
static void subscribed(const std::error_code& error, const worker_uuid& worker)
{
    if (error)
    {
        // This command only halts on failure.
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
        stopped = true;
    }
    else
    {
        // TODO: localize
        std::cout << "Waiting for updates..." << std::endl;
    }
}

// TODO: stopped should be passed here via closure
// or by converting this to a member function.
static void subscription_handler(const std::error_code& error, size_t height,
    const hash_digest& block_hash, const transaction_type& tx)
{
    if (error)
    {
        // This command only halts on failure.
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
        stopped = true;
    }
    else
    {
        // TODO: localize
        std::cout << "Update " << hash_transaction(tx)
            << " [ #" << height << " " << block_hash << " ]" << std::endl;
    }
}

console_result monitor::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const auto bitfield = get_bitfield_option();
    const auto number_bits = get_number_bits_option();

    stealth_prefix prefix{ 0, 0 };
    if (number_bits > 0)
    {
        // TODO: set bitfield and number_bits into prefix.

        // NOTE: this defined a single uint32 prefix value but it's 
        // not clear to me how this can accomdate the intent of the
        // bitfield and number of bits design.
    }

    stopped = false;
    result = console_result::okay;

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.address.subscribe(prefix, subscription_handler, subscribed);
    client.poll(stopped);

    return result;
}

