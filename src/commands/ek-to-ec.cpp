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
#include <bitcoin/explorer/commands/ek-to-ec.hpp>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/ec_private.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;

console_result ek_to_ec::invoke(std::ostream& output, std::ostream& error)
{
#ifdef WITH_ICU
    const auto& passphrase = get_passphrase_argument();
    const auto& key = get_ek_private_key_argument();

    bool unused1;
    uint8_t unused2;
    ec_secret secret;
    if (!decrypt(secret, unused2, unused1, key, passphrase))
    {
        error << BX_EK_TO_EC_INVALID_PASSPHRASE << std::endl;
        return console_result::failure;
    }

    output << config::ec_private(secret) << std::endl;
    return console_result::okay;
#else
    error << BX_EK_TO_EC_REQUIRES_ICU << std::endl;
    return console_result::failure;
#endif
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
