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

#include <bitcoin/explorer/commands/hd-to-public.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result hd_to_public::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto secret_version = get_secret_version_option();
    const auto version = get_version_option();
    const auto& key = get_hd_key_argument();

    if (key.version() != secret_version)
    {
        output << BX_HD_TO_PUBLIC_VERSION_MISMATCH << std::endl;
        return console_result::failure;
    }

    const auto prefixes = wallet::hd_private::to_prefixes(secret_version,
        version);

    const wallet::hd_private private_key(key, prefixes);

    if (!private_key)
    {
        output << BX_HD_TO_PUBLIC_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << private_key.to_public() << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
