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
#include <bitcoin/explorer/commands/stealth-encode.hpp>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result stealth_encode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto version = get_version_option();
    const auto& filter = get_filter_option();
    const auto& scan = get_scan_pubkey_argument();
    const ec_compressed& spend = get_spend_pubkey_argument();

    if (filter.size() > stealth_address::max_filter_bits)
    {
        error << BX_STEALTH_ENCODE_FILTER_TOO_LONG << std::endl;
        return console_result::failure;
    }

    const stealth_address address(filter, scan, { spend }, 0, version);

    output << address << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
