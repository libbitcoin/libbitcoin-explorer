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
#include <sx/obelisk.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/serializer/sha256.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: this should be a member of sx::extensions::fetch_stealth,
// otherwise concurrent test execution will collide on shared state.
static bool node_stopped = false;

// TODO: node_stopped should be passed here via closure
// or by converting this to a member function.
static void stealth_fetched(const std::error_code& error,
    const blockchain::stealth_list& stealth_results)
{
    if (error)
        std::cerr << error.message() << std::endl;
    else
        for (const blockchain::stealth_row& row: stealth_results)
            std::cout << boost::format(SX_FETCH_STEALTH_TEXT_OUTPUT) %
                bytes(row.ephemkey) % row.address.encoded() % 
                sha256(row.transaction_hash);

    node_stopped = true;
}

console_result fetch_stealth::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    auto height = get_height_option();
    auto bitfield = get_bitfield_argument();

    // TODO: verify that these are equivalent.
    //stealth_prefix prefix(prefix_str);
    stealth_prefix prefix(bitfield);

    OBELISK_FULLNODE(pool, fullnode);
    fullnode.blockchain.fetch_stealth(prefix, 
        std::bind(stealth_fetched, std::placeholders::_1, 
            std::placeholders::_2), height);
    poll(fullnode, pool, node_stopped);
    return console_result::okay;
}