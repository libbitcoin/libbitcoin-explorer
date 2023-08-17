/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/ek-to-ec.hpp>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

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

    output << base16(secret) << std::endl;
    return console_result::okay;
#else
    error << BX_EK_TO_EC_REQUIRES_ICU << std::endl;
    return console_result::failure;
#endif
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
