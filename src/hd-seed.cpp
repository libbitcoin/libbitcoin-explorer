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
#include <wallet/wallet.hpp>
#include <sx/command/hd-seed.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result hd_seed::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return console_result::failure;

    const size_t seed_entropy_bytes = 32;
    data_chunk entropy(argc > 1 ? decode_hex(argv[1]) : 
        random_fill(seed_entropy_bytes));

    // See notes in config.h regarding setting symbolic names and typed values.
    config_map_type config;
    get_config(config);
    const auto is_testnet = is_true(config[SX_SETTING_TESTNET]);

    hd_private_key private_key(entropy, is_testnet);
    std::cout << private_key.serialize() << std::endl;
    return console_result::okay;
}

