/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/commands/ek-address.hpp>

#include <algorithm>
#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result ek_address::invoke(std::ostream& output, std::ostream& error)
{
    const auto uncompressed = get_uncompressed_option();
    const auto version = get_version_option();
    const auto& token = get_token_argument();
    const data_chunk& seed = get_seed_argument();

    if (seed.size() < ek_seed_size)
    {
        error << BX_EK_ADDRESS_SHORT_SEED << std::endl;
        return console_result::failure;
    }

    ek_seed bytes;
    std::copy(seed.begin(), seed.begin() + ek_seed_size, bytes.begin());
    const auto compressed = !uncompressed;

    ec_compressed point;
    encrypted_private unused;
    create_key_pair(unused, point, token, bytes, version, compressed);
    const payment_address address({ point, compressed }, version);

    output << address << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
