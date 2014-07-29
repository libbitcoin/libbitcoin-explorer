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
#include <sx/command/fetch-stealth.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/define.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/serializer/bitcoin256.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: this should be a member of sx::extensions::fetch_stealth,
// otherwise concurrent test execution will collide on shared state.
static bool node_stopped;
static console_result result;

// TODO: node_stopped should be passed here via closure
// or by converting this to a member function.
static void stealth_fetched(const std::error_code& error,
    const blockchain::stealth_list& stealth_results)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
    }
    else
        for (const blockchain::stealth_row& row : stealth_results)
            std::cout << boost::format(SX_FETCH_STEALTH_OUTPUT) %
                bytes(row.ephemkey) % address(row.address) %
                sx::serializer::bitcoin256(row.transaction_hash);

    node_stopped = true;
}

console_result fetch_stealth::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto bitfield = get_bitfield_option();
    const auto number_bits = get_number_bits_option();
    const auto from_height = get_from_height_option();

    stealth_prefix prefix{ 0, 0 };
    if (number_bits > 0)
    {
        // TODO: set bitfield and number_bits into prefix.

        // NOTE: a later version of SX was updated to use a single
        // uint32 prefix value but it's not clear to me how this can
        // accomdate the intent of the bitfield and number of bits
        // design.
    }

    node_stopped = false;
    result = console_result::okay;

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.blockchain.fetch_stealth(prefix,
        std::bind(stealth_fetched, ph::_1, ph::_2), from_height);
    client.poll(node_stopped);

    return result;
}