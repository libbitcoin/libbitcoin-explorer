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
#include <sx/command/ec-new.hpp>

#include <iostream>
#include <wallet/wallet.hpp>
#include <sx/serializer/hd_private.hpp>
#include <sx/utility/utility.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result ec_new::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Arbitrary 256 bit length for generated seeds.
    constexpr size_t fill_seed_size = 32;

    // Bound parameters.
    data_chunk seed = get_seed_argument();
    const bool testnet = get_general_testnet_setting();

    if (seed.size() == 0)
    {
        seed.resize(fill_seed_size);
        random_fill(seed);
    }

    // Using HD key generation because we edon't have one for EC.
    const hd_private_key hd_key(seed, testnet);
    const ec_secret ec_key = hd_key.private_key();

    output << ec_private(ec_key) << std::endl;
    return console_result::okay;
}