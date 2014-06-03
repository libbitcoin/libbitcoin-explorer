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
#include <bitcoin/bitcoin.hpp>
#include <sx/command/stealth-addr.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/dispatch.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result stealth_addr::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 2))
        return console_result::failure;

    bool reuse_address = false;
    uint8_t number_sigs = 0;
    std::vector<std::string> args;

    // Get options and fill args vector.
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (is_option(arg, SX_OPTION_REUSE_KEY))
            continue;
        if (is_option(arg, SX_OPTION_SIGNATURES))
        {
            ++i;
            if (i == argc)
            {
                std::cerr << "sx: --signatures requires a number." << std::endl;
                return console_result::failure;
            }
            if (!parse<uint8_t>(arg, number_sigs))
            {
                std::cerr << "sx: --signatures value is invalid." << std::endl;
                return console_result::failure;
            }
            continue;
        }

        args.push_back(arg);
    }

    // Read scan pubkey.
    if (args.empty())
    {
        std::cerr << "sx: Scan pubkey must be provided." << std::endl;
        return console_result::failure;
    }

    // Remove the first value as the scan_pubkey.
    const auto scan_pubkey = decode_hex(args.front());
    args.erase(args.begin());

    // Read spend pubkeys.
    if (args.size() > std::numeric_limits<uint8_t>::max())
    {
        std::cerr << "sx: Too many spend pubkeys." << std::endl;
        return console_result::failure;
    }

    // Remaining keys are spend_pubkeys.
    typedef std::vector<data_chunk> pubkey_list;
    pubkey_list spend_pubkeys;
    for (const auto& arg: args)
        spend_pubkeys.emplace_back(decode_hex(arg));

    // Now we have the data.
    // Construct actual address.
    // https://wiki.unsystem.net/index.php/DarkWallet/Stealth#Address_format
    data_chunk raw_addr;
    // version byte.
    raw_addr.push_back({0x2a});
    // options byte.
    uint8_t options_bitfield = 0;
    if (reuse_address)
        options_bitfield |= 1;
    raw_addr.push_back(options_bitfield);
    extend_data(raw_addr, scan_pubkey);
    const auto number_keys = static_cast<uint8_t>(spend_pubkeys.size());
    raw_addr.push_back(number_keys);
    for (const auto& pubkey: spend_pubkeys)
        extend_data(raw_addr, pubkey);
    // If not configured then set it to the number_keys
    if (!number_sigs)
        number_sigs = number_keys;
    if (reuse_address)
        ++number_sigs;
    raw_addr.push_back(number_sigs);
    // Prefix filter currently unused.
    // Allow configuring this later.
    raw_addr.push_back({0x00});
    const auto checksum = bitcoin_checksum(raw_addr);
    append_checksum(raw_addr);
    const auto stealth_addr = encode_base58(raw_addr);
    std::cout << stealth_addr << std::endl;
    return console_result::okay;
}

