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

bool stopped = false;

void tx_validated(const std::error_code& ec, const index_list& unconfirmed)
{
    std::cout << "Status: " << ec.message() << std::endl;
    for (size_t unconfirmed_index: unconfirmed)
        std::cout << "  Unconfirmed: " << unconfirmed_index << std::endl;
    stopped = true;
}

bool invoke(const int argc, const char* argv[])
{
    if (argc != 1 && argc != 2)
    {
        std::cout << "Usage: sx validtx FILENAME" << std::endl;
        return 1;
    }
    std::string filename;
    if (argc == 1)
        filename = "-";
    else
        filename = argv[1];
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
    config_map_type config;
    get_config(config);
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    fullnode.transaction_pool.validate(tx, tx_validated);
    while (!stopped)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    pool.stop();
    pool.join();
    return 0;
}

