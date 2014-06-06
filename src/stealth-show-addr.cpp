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
#include <stdint.h>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/command/stealth-show-addr.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/dispatch.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result stealth_show_addr::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 2, 2))
        return console_result::failure;

    const std::string stealth(argv[1]);

    // TODO: This should be consumed by dispatch.
    if (is_option(stealth, SX_OPTION_HELP))
    {
        example();
        return console_result::okay;
    }

    stealth_address address;
    if (!address.set_encoded(stealth))
    {
        std::cerr << "sx: Invalid stealth address." << std::endl;
        return console_result::failure;
    }

    // Now display fields.
    std::cout << "Options: ";
    if (flags_set(address.options, stealth_address::flags::reuse_key))
        std::cout << "reuse_key";
    else
        std::cout << "none";
    std::cout << std::endl;
    std::cout << "Scan pubkey: " << address.scan_pubkey << std::endl;
    std::cout << "Spend pubkeys:" << std::endl;
    for (const auto& pubkey : address.spend_pubkeys)
        std::cout << "  " << pubkey << std::endl;
    std::cout << "Number required signatures: "
        << address.number_signatures << std::endl;

    // Display prefix.
    // TODO: provide serialization override on address_prefix.
    // TODO: verify that if the prefix is empty() it serializes to "".
    std::string prefix(serialize(address.prefix, "none"));

    std::cout << "Prefix: " << prefix << std::endl;
    return console_result::okay;
}

