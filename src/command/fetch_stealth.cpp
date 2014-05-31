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

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

bool stopped = false;

void stealth_fetched(const std::error_code& ec,
    const blockchain::stealth_list& stealth_results)
{
    if (ec)
    {
        log_error() << "Stealth fetch failed: " << ec.message();
        stopped = true;
        return;
    }
    for (const blockchain::stealth_row& row: stealth_results)
        std::cout << "ephemkey: " << row.ephemkey
            << " address: " << row.address.encoded()
            << " tx_hash: " << row.transaction_hash << std::endl;
    stopped = true;
}

bool invoke(const int argc, const char* argv[])
{
    if (argc > 3)
    {
        std::cerr << "Usage: fetch-stealth BITFIELD [FROM_HEIGHT]"
            << std::endl;
        return -1;
    }
    size_t from_height = 0;
    if (argc == 3)
        from_height = boost::lexical_cast<size_t>(argv[2]);
    stealth_prefix prefix;
    if (argc >= 2)
        prefix = stealth_prefix(std::string(argv[1]));
    // Start Obelisk
    config_map_type config;
    get_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    // Perform query.
    fullnode.blockchain.fetch_stealth(prefix,
        std::bind(stealth_fetched, _1, _2), from_height);
    while (!stopped)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    pool.stop();
    pool.join();
    return 0;
}

