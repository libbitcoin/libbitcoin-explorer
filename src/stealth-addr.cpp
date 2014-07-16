/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <sx/command/stealth-addr.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/serializer/base58.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: name 'some_flag' and move to flags enum.
// TODO: enable prefix filter, currently unused.
// TODO: Is testnet used here, it was loaded by not referenced
// TODO: there should be validation on input key values, length only?
// 100% coverage by line, loc ready.
console_result stealth_addr::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    auto signatures = get_signatures_option();
    auto reuse_key = get_reuse_key_option();
    const auto scan_key = get_scan_key_argument();
    const auto spend_keys = get_spend_keys_argument();

    // Construct actual address.
    // https://wiki.unsystem.net/index.php/DarkWallet/Stealth#Address_format
    data_chunk raw_address;

    const uint8_t some_flag = 1;
    const uint8_t stealth_version = 0x2a;
    const uint8_t default_stealth_prefix_filter = 0x00;
    const uint8_t options_bitfield = if_else(reuse_key, some_flag, 0);
    const uint8_t number_keys = spend_keys.size();

    raw_address.push_back(stealth_version);
    raw_address.push_back(options_bitfield);
    extend_data(raw_address, static_cast<bc::data_chunk>(scan_key));
    raw_address.push_back(number_keys);

    for (const auto& spend_key : spend_keys)
        extend_data(raw_address, static_cast<bc::data_chunk>(spend_key));
    
    // If not configured then set it to the number_keys.
    if (signatures == 0)
        signatures = number_keys;

    // if reusing the address increment the number of signatures.
    if (reuse_key)
        ++signatures;

    raw_address.push_back(signatures);
    raw_address.push_back(default_stealth_prefix_filter);
    append_checksum(raw_address);

    // Return the results.
    output << base58(raw_address) << std::endl;
    return console_result::okay;
}