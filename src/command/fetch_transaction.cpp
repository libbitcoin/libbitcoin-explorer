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
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include "config.hpp"
#include <sx/utility/console.hpp>

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

bool stopped = false;

void tx_fetched_main(const std::error_code& ec, const transaction_type& tx)
{
    if (ec)
    {
        std::cerr << "fetch-transaction: " << ec.message() << std::endl;
        stopped = true;
    }
    else
    {
        data_chunk raw_tx(satoshi_raw_size(tx));
        satoshi_save(tx, raw_tx.begin());
        std::cout << raw_tx << std::endl;
        stopped = true;
    }
}

void tx_fetched(const std::error_code& ec, const transaction_type& tx,
    const hash_digest& tx_hash, obelisk::fullnode_interface& fullnode)
{
    if (ec == error::not_found)
    {
        // Try tx memory pool instead.
        fullnode.transaction_pool.fetch_transaction(tx_hash, tx_fetched_main);
        return;
    }
    tx_fetched_main(ec, tx);
}

bool invoke(const int argc, const char* argv[])
{
    std::string tx_hash_str;
    if (argc == 2)
        tx_hash_str = argv[1];
    else
        tx_hash_str = read_stdin();
    hash_digest tx_hash = decode_hash(tx_hash_str);
    config_map_type config;
    get_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    fullnode.blockchain.fetch_transaction(tx_hash,
        std::bind(tx_fetched, _1, _2, tx_hash, std::ref(fullnode)));
    while (!stopped)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    pool.stop();
    pool.join();
    return 0;
}

