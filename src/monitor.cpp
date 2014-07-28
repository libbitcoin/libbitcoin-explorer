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
using namespace sx;
using namespace sx::extension;
using std::placeholders::_1;
using std::placeholders::_2;

// NOTE: this wasn't called.
//static void history_fetched(const std::error_code& error,
//    const blockchain::history_list& history)
//{
//    if (error)
//    {
//        std::cerr << "history: Failed to fetch history: "
//            << error.message() << std::endl;
//        return;
//    }
//
//    for (const auto& row: history)
//    {
//        int64_t value = row.value;
//        std::cout << row.output.hash << " " << value << std::endl;
//        if (row.spend.hash != null_hash)
//            std::cout << row.spend.hash << " " << -value << std::endl;
//    }
//}

//// TODO: this should be a member of sx::extensions::subscribed,
//// otherwise concurrent test execution will collide on shared state.
//static bool node_stopped = false;
//
//// TODO: node_stopped should be passed here via closure
//// or by converting this to a member function.
//static void subscribed(const std::error_code& error,
//    const obelisk::worker_uuid& worker)
//{
//    if (error)
//        std::cerr << "Error: " << error.message() << std::endl;
//    else
//        std::cout << "Subscribed." << std::endl;
//
//    // NOTE: added this here, otherwise we have a halting problem, test.
//    node_stopped = true;
//}
//
//static void new_update(const std::error_code& ec,
//    size_t height, const hash_digest& block_hash, const transaction_type& tx)
//{
//    std::cout << "Update " << hash_transaction(tx)
//        << " [ #" << height << " " << block_hash << " ]" << std::endl;
//}

console_result monitor::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const auto prefix = get_prefix_argument();

    cerr << SX_MONITOR_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;

    //std::cerr << std::endl;
    //std::cerr << "**************************************" << std::endl;
    //std::cerr << "Warning: this command is experimental." << std::endl;
    //std::cerr << "**************************************" << std::endl;
    //std::cerr << std::endl;

    //std::string bits(argv[1]);
    //obelisk::address_prefix prefix(bits);

    //OBELISK_FULLNODE(pool, fullnode);
    //fullnode.address.subscribe(prefix, new_update, subscribed);
    //poll(fullnode, pool, node_stopped);
    //return console_result::okay;
}

