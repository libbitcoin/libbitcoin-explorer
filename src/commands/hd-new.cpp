/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#include "precompile.hpp"
#include <explorer/commands/hd-new.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/hd_priv.hpp>

using namespace bc;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

// 83% coverage by line, loc ready. BX_HD_NEW_INVALID_KEY uncovered.
console_result hd_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const data_chunk& seed = get_seed_argument();
    const bool testnet = get_general_testnet_setting();

    if (seed.size() < minimum_seed_size)
    {
        error << BX_HD_NEW_SHORT_SEED << std::endl;
        return console_result::failure;
    }

    // TESTNET OPTION DOES NOT REQUIRE RECOMPILE
    const hd_private_key key(seed, testnet);
    if (!key.valid())
    {
        error << BX_HD_NEW_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << hd_priv(key) << std::endl;
    return console_result::okay;
}