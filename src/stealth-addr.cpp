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
#include <iostream>
#include <string>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <boost/program_options.hpp>
#include <sx/command.hpp>
#include <sx/command/stealth-addr.hpp>
#include <sx/generated.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/environment.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result stealth_addr::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    auto signatures = get_signatures_option();
    const auto reuse_key = get_reuse_key_option();
    const auto encoded_scan_pubkey = get_scan_pubkey_argument();
    const auto encoded_spend_pubkeys = get_spend_pubkeys_argument();
    const auto testnet = get_general_testnet_setting();

    // TODO: figure out how to incorporate standard deserialization into the
    // boost::program_options::value_semantic definition so we can skip this.
    // ------------------------------------------------------------------------
    // Decode raw parameters.
    // TODO: there should be validation on input key values, length only?
    const auto scan_pubkey = decode_hex(encoded_scan_pubkey);
    typedef std::vector<data_chunk> pubkey_list;
    pubkey_list spend_pubkeys;
    for (const auto& spend_pubkey: encoded_spend_pubkeys)
        spend_pubkeys.emplace_back(decode_hex(spend_pubkey));
    // ------------------------------------------------------------------------

    // Construct actual address.
    // https://wiki.unsystem.net/index.php/DarkWallet/Stealth#Address_format
    data_chunk raw_addr;

    // TODO: name 'some_flag' and move to flags enum.
    const uint8_t some_flag = 1;
    const uint8_t stealth_version = 0x2a;
    const uint8_t default_stealth_prefix_filter = 0x00;
    const uint8_t options_bitfield = if_else(reuse_key, some_flag, 0);
    const uint8_t number_keys = static_cast<uint8_t>(spend_pubkeys.size());

    raw_addr.push_back(stealth_version);
    raw_addr.push_back(options_bitfield);

    extend_data(raw_addr, scan_pubkey);
    raw_addr.push_back(number_keys);

    for (const auto& pubkey: spend_pubkeys)
        extend_data(raw_addr, pubkey);
    
    // If not configured then set it to the number_keys.
    if (signatures == 0)
        signatures = number_keys;

    // if reusing the address increment the number of signatures.
    if (reuse_key)
        ++signatures;

    raw_addr.push_back(signatures);

    // TODO: enable this feature later (Prefix filter currently unused).
    raw_addr.push_back(default_stealth_prefix_filter);

    const auto checksum = bitcoin_checksum(raw_addr);
    append_checksum(raw_addr);
    const auto stealth_addr = encode_base58(raw_addr);

    // Return the results.
    line_out(output, stealth_addr);
    return console_result::okay;
}

