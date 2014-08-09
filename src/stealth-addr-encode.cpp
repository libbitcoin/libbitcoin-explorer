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
#include <sx/command/stealth-addr-encode.hpp>

#include <iostream>
#include <stdint.h>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/base58.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// 100% coverage by line, loc ready.
console_result stealth_addr_encode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const uint8_t signatures = get_signatures_option();
    const auto reuse_key = get_reuse_key_option();
    const stealth_prefix& prefix = get_prefix_option();
    const ec_point& scan_key = get_scan_key_argument();
    const auto& spend_keys = get_spend_keys_argument();
    const auto testnet = get_general_testnet_setting();

    // Construct actual address.
    // https://wiki.unsystem.net/index.php/DarkWallet/Stealth#Address_format
    data_chunk stealth;

    // TESTNET WORKS WITHOUT RECOMPILE
    const uint8_t version = if_else(testnet, 0x2b, 0x2a);

    constexpr uint8_t reuse_flag = stealth_address::flags::reuse_key;
    const uint8_t options = if_else(reuse_key, reuse_flag, 0);
    const auto number_keys = static_cast<uint8_t>(spend_keys.size());
    const auto numeric_prefix = static_cast<uint32_t>(prefix.to_ulong());

    stealth.push_back(version);
    stealth.push_back(options);
    extend_data(stealth, scan_key);
    stealth.push_back(number_keys);

    for (const ec_point& spend_key: spend_keys)
        extend_data(stealth, spend_key);
    
    // If not specified then set signatures to the number_keys.
    auto sigs = if_else(signatures == 0, number_keys, signatures);

    // if reusing the address increment the number of signatures.
    sigs = if_else(reuse_key, sigs + 1, sigs);

    stealth.push_back(sigs);
    stealth.push_back(numeric_prefix);
    append_checksum(stealth);

    output << base58(stealth) << std::endl;
    return console_result::okay;
}