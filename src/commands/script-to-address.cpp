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

#include <bitcoin/explorer/commands/script-to-address.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/address.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result script_to_address::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& script = get_script_argument();
    const auto version = get_version_option();

    // We use zero as a sentinel as it is invalid as any coin's p2sh version.
    uint8_t address_version = version;
    if (version == 0)
        address_version = bc::wallet::payment_address::script_version;
        
    // Make ripemd hash of serialized script.
    const auto serialized_script = script.to_data();
    const auto bitcoin160 = bitcoin_short_hash(serialized_script);

    // TESTNET VERSION REQUIRES RECOMPILE TO USE DEFAULT VERSION
    address script_hash_address(address_version, bitcoin160);

    output << script_hash_address << std::endl;
    return console_result::okay;
}
