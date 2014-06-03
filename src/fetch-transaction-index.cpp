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
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/command/fetch-transaction-index.hpp>
#include <sx/utility/client.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

// TODO: this should be a member of sx::extensions::fetch_transaction_index,
// otherwise concurrent test execution will collide on shared state.
static bool node_stopped = false;

// TODO: node_stopped should be passed here via closure
// or by converting this to a member function.
static void transaction_index_fetched(const std::error_code& ec, 
    const size_t height, size_t index)
{
    if (ec)
        std::cerr << "fetch-transaction: " << ec.message() << std::endl;
    else
    {
        std::cout << "Height: " << height << std::endl;
        std::cout << "Index: " << index << std::endl;
    }

    node_stopped = true;
}

console_result fetch_transaction_index::invoke(const int argc, 
    const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return console_result::failure;

    std::string tx_hash_str(get_arg_or_stream(argc, argv, std::cin));
    hash_digest tx_hash = decode_hash(tx_hash_str);

    OBELISK_FULLNODE(pool, fullnode);
    fullnode.blockchain.fetch_transaction_index(tx_hash, 
        transaction_index_fetched);
    poll(fullnode, pool, node_stopped);

    return console_result::okay;
}

