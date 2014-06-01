/*
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
#include <sx/command/fetch-transaction.hpp>
#include <sx/utility/client.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

// TODO: this should be a member of sx::extensions::fetch_transaction,
// otherwise concurrent test execution will collide on shared state.
bool fetch_transaction_stopped = false;

// TODO: fetch_transaction_stopped should be passed here via closure
// or by converting this to a member function.
void transaction_fetched(const std::error_code& ec, const transaction_type& tx)
{
    if (ec)
        std::cerr << "fetch-transaction: " << ec.message() << std::endl;
    else
    {
        data_chunk raw_tx(satoshi_raw_size(tx));
        satoshi_save(tx, raw_tx.begin());
        std::cout << raw_tx << std::endl;
    }

    fetch_transaction_stopped = true;
}

// Try the tx memory pool if the transaction is not in the blockchain.
void transaction_fetched_wrapper(const std::error_code& ec, 
    const transaction_type& tx, const hash_digest& tx_hash, 
    obelisk::fullnode_interface& fullnode)
{
    if (ec == error::not_found)
        fullnode.transaction_pool.fetch_transaction(tx_hash, 
            transaction_fetched);
    else
        transaction_fetched(ec, tx);
}

bool sx::extensions::fetch_transaction::invoke(const int argc,
    const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return false;

    std::string tx_hash_str(argc == 1 ? read_stdin() : argv[1]);
    hash_digest tx_hash = decode_hash(tx_hash_str);

    OBELISK_FULLNODE(pool, fullnode);
    fullnode.blockchain.fetch_transaction(tx_hash,
        std::bind(transaction_fetched_wrapper, _1, _2, tx_hash, 
            std::ref(fullnode)));
    poll(fullnode, pool, fetch_transaction_stopped);

    return true;
}

