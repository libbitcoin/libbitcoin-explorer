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
#include <bitcoin/explorer/commands/hd-to-public.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::wallet;

console_result hd_to_public::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto version = get_version_option();
    const auto& private_key = get_hd_private_key_argument();

    // TODO: deriving public from private requires prefix configuration.

    // Obtain private version and combine with specified public version.
    using secret = bc::wallet::hd_private;
    const auto private_hd_key = private_key.to_hd_key();
    const auto prefix = secret::to_prefix(private_key.lineage().prefixes);
    const auto prefixes = secret::to_prefixes(prefix, version);

    // Derive the public key from new private key with the public version.
    const secret versioned(private_hd_key, prefixes);

    output << versioned.to_public() << std::endl;
    return console_result::okay;
}
