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
#include <random>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include "config.hpp"

using namespace bc;
using namespace libwallet;

data_chunk random_bytes(size_t size)
{
    std::random_device rd;
    std::default_random_engine engine(rd());

    // std::uniform_int_distribution requires at least 16 bits on msvc builds.
    std::uniform_int_distribution<uint16_t> 
        uniform_dist(0, std::numeric_limits<uint16_t>::max());

    data_chunk result;
    for (size_t i = 0; i < size; ++i)
        result.push_back(static_cast<uint8_t>(uniform_dist(engine) >> 8));
    return result;
}

bool invoke(const int argc, const char* argv[])
{
    if (argc > 2)
    {
        std::cerr << "Usage: sx hd-seed [ENTROPY]" << std::endl;
        return -1;
    }
    data_chunk entropy;
    if (argc == 2)
        entropy = decode_hex(argv[1]);
    else
        entropy = random_bytes(32);

    config_map_type config;
    get_config(config);

    bool testnet;
    if (config["testnet"] == "true")
	testnet = true;
    else
	testnet = false;

    hd_private_key hd_key(entropy, testnet);
    std::cout << hd_key.serialize() << std::endl;
    return 0;
}

