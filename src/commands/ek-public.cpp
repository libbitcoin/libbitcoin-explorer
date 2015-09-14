/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#include <bitcoin/explorer/commands/ek-public.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::wallet;

console_result commands::ek_public::invoke(std::ostream& output,
    std::ostream& error)
{
    const auto uncompressed = get_uncompressed_option();
    const auto version = get_version_option();
    const auto& token = get_token_argument();
    const data_chunk& seed = get_seed_argument();

    if (seed.size() < ek_seed_size)
    {
        error << BX_EK_PUBLIC_SHORT_SEED << std::endl;
        return console_result::failure;
    }
    
    ek_seed bytes;
    std::copy(seed.begin(), seed.begin() + ek_seed_size, bytes.begin());

    ec_point unused1;
    ek_private unused2;
    config::ek_public key;
    create_key_pair(unused2, key.data(), unused1, token, bytes, version,
        !uncompressed);
    
    output << key << std::endl;
    return console_result::okay;
}
