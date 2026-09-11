/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Sponsored in part by Digital Contract Design, LLC

#include <bitcoin/explorer/commands/match-neutrino-address.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result match_neutrino_address::invoke(std::ostream& output, std::ostream&)
{
    // Bound parameters.
    const neutrino::block_filter filter
    {
        get_block_hash_argument(),
        get_client_filter_argument()
    };

    if (!neutrino::match_filter(filter, get_address_argument(),
        get_wallet_pay_to_public_key_hash_version_setting(),
        get_wallet_pay_to_script_hash_version_setting()))
    {
        output << BX_FILTER_MATCH_ADDRESS_FAILURE << std::endl;
        return console_result::invalid;
    }

    output << BX_FILTER_MATCH_ADDRESS_SUCCESS << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
