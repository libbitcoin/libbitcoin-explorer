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
#include <bitcoin/explorer/commands/stealth-encode.hpp>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::wallet;

console_result stealth_encode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto version = get_version_option();
    const auto& filter = get_prefix_option();
    const auto& scan_pubkey = get_scan_pubkey_argument();
    const auto& spend_pubkeys = get_spend_pubkeys_argument();
    const auto& signatures = get_signatures_option();

    const size_t maximum = std::max(size_t(1), spend_pubkeys.size());

    if (signatures > maximum)
    {
        error << BX_STEALTH_ENCODE_SIGNATURES_OVERFLOW << std::endl;
        return console_result::failure;
    }

    // TODO: finish stealth multisig implemetation.
    // Issue a warning but don't prevent experimentation.
    if (spend_pubkeys.size() > 1u)
        error << BX_STEALTH_ENCODE_MULTISIG_NOT_SUPPORTED << std::endl;

    if (filter.size() > stealth_address::max_filter_bits)
    {
        error << BX_STEALTH_ENCODE_PREFIX_TOO_LONG << std::endl;
        return console_result::failure;
    }

    // TODO: if not set default version from config (address_stealth).

    const auto spend_points = cast<ec_public, ec_compressed>(spend_pubkeys);
    const stealth_address address(filter, scan_pubkey, spend_points,
        signatures, version);

    output << address << std::endl;
    return console_result::okay;
}
