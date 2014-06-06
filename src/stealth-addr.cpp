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

bool capture_signatures(int argc, const char* argv[], 
    std::vector<std::string> args, uint8_t& signatures, bool& reuse_address)
{
    signatures = 0;
    reuse_address = false;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (is_option(arg, SX_OPTION_REUSE_KEY))
        {
            reuse_address = true;
            continue;
        }

        if (is_option(arg, SX_OPTION_SIGNATURES))
        {
            if (++i == argc)
            {
                std::cerr << "sx: --signatures requires a number." << std::endl;
                return false;
            }

            if (!parse(signatures, arg))
            {
                std::cerr << "sx: --signatures value is invalid." << std::endl;
                return false;
            }

            continue;
        }

        args.push_back(arg);
    }

    return true;
}

console_result stealth_addr::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 2))
        return console_result::failure;

    uint8_t number_sigs;
    bool reuse_address = false;
    std::vector<std::string> args;

    if (!capture_signatures(argc, argv, args, number_sigs, reuse_address))
        return console_result::failure;

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

    // Now we have the data, construct actual address.
    // https://wiki.unsystem.net/index.php/DarkWallet/Stealth#Address_format
    data_chunk raw_addr;

    // TODO: name 'some_flag' and move to flags enum.
    const uint8_t some_flag = 1;
    const uint8_t stealth_version = 0x2a;
    const uint8_t default_stealth_prefix_filter = 0x00;
    const uint8_t options_bitfield = if_else(reuse_address, some_flag, 0);
    const uint8_t number_keys = static_cast<uint8_t>(spend_pubkeys.size());

    raw_addr.push_back(stealth_version);
    raw_addr.push_back(options_bitfield);

    extend_data(raw_addr, scan_pubkey);
    raw_addr.push_back(number_keys);

    for (const auto& pubkey: spend_pubkeys)
        extend_data(raw_addr, pubkey);
    
    // If not configured then set it to the number_keys
    if (number_sigs == 0)
        number_sigs = number_keys;

    // if reusing the address increment the number of signatures.
    if (reuse_address)
        ++number_sigs;

    raw_addr.push_back(number_sigs);

    // TODO: enable this feature later (Prefix filter currently unused).
    raw_addr.push_back(default_stealth_prefix_filter);

    const auto checksum = bitcoin_checksum(raw_addr);
    append_checksum(raw_addr);
    const auto stealth_addr = encode_base58(raw_addr);
    return console_result::okay;
}

