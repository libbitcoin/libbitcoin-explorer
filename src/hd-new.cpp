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
#include <sx/command/hd-new.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hd_private.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// 83% coverage by line, loc ready. SX_HD_NEW_INVALID_KEY uncovered.
console_result hd_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const data_chunk& seed = get_seed_argument();
    const bool testnet = get_general_testnet_setting();

    // Arbitrary minimum 128 bit length for generated seeds.
    constexpr size_t minimum_seed_size = 128;
    if (seed.size() * byte_size < minimum_seed_size)
    {
        error << SX_HD_NEW_SHORT_SEED << std::endl;
        return console_result::failure;
    }

    // TESTNET OPTION DOES NOT REQUIRE RECOMPILE
    const hd_private_key key(seed, testnet);
    if (!key.valid())
    {
        error << SX_HD_NEW_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << hd_private(key) << std::endl;
    return console_result::okay;
}