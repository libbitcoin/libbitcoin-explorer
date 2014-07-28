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
#include <sx/command/fetch-transaction.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: this should be a member of sx::extensions::fetch_transaction,
// otherwise concurrent test execution will collide on shared state.
static bool node_stopped;
static console_result result;

// TODO: abstract formats.
// TODO: node_stopped should be passed here via closure
// or by converting this to a member function.
static void transaction_fetched(const std::error_code& error, 
    const transaction_type& tx_type)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
    }
    else
    {
        data_chunk raw_tx(satoshi_raw_size(tx_type));
        satoshi_save(tx_type, raw_tx.begin());
        std::cout << bytes(raw_tx) << std::endl;
    }

    node_stopped = true;
}

// Try the tx memory pool if the transaction is not in the blockchain.
static void transaction_fetched_wrapper(const std::error_code& ec,
    const transaction_type& tx_type, const hash_digest& hash,
    obelisk::fullnode_interface& fullnode)
{
    if (ec == error::not_found)
        fullnode.transaction_pool.fetch_transaction(hash, transaction_fetched);
    else
        transaction_fetched(ec, tx_type);
}

console_result fetch_transaction::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    auto hash = get_hash_argument();

    node_stopped = false;
    result = console_result::okay;

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.blockchain.fetch_transaction(hash,
        std::bind(transaction_fetched_wrapper, std::placeholders::_1,
            std::placeholders::_2, hash, std::ref(fullnode)));
    client.poll(node_stopped);

    return result;
}

