/**
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
#include <wallet/wallet.hpp>
#include <sx/command/stealth-show-addr.hpp>

using namespace bc;
using namespace libwallet;

void show_usage()
{
    std::cerr << "Usage: sx stealth-show-addr STEALTH_ADDRESS" << std::endl;
}

bool invoke(const int argc, const char* argv[])
{
    if (argc != 2)
    {
        show_usage();
        return -1;
    }
    const std::string stealth_str = argv[1];
    if (stealth_str == "--help" || stealth_str == "-h")
    {
        show_usage();
        return -1;
    }
    stealth_address addr;
    if (!addr.set_encoded(stealth_str))
    {
        std::cerr << "sx: Invalid stealth address." << std::endl;
        return -2;
    }
    // Now display fields.
    std::cout << "Options: ";
    if (addr.options & stealth_address::reuse_key_option)
        std::cout << "reuse_key";
    else
        std::cout << "none";
    std::cout << std::endl;
    std::cout << "Scan pubkey: " << addr.scan_pubkey << std::endl;
    std::cout << "Spend pubkeys:" << std::endl;
    for (const auto& pubkey: addr.spend_pubkeys)
        std::cout << "  " << pubkey << std::endl;
    std::cout << "Number required signatures: "
        << addr.number_signatures << std::endl;
    // Display prefix.
    std::string prefix_str = "none";
    if (!addr.prefix.empty())
        boost::to_string(addr.prefix, prefix_str);
    std::cout << "Prefix: " << prefix_str << std::endl;
    return 0;
}

