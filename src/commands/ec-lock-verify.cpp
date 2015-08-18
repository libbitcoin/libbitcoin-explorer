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

#include <bitcoin/explorer/commands/ec-lock.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/ec_private.hpp>

using namespace bc;
using namespace bc::bip38;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result ec_lock_verify::invoke(std::ostream& output, std::ostream& error)
{
    const auto& passphrase = get_passphrase_argument();
    const auto& confirmation = get_confirmation_argument();

    std::string address;

    const auto confirmed = bip38_lock_verify(
        base58(confirmation), passphrase, address);

    if (confirmed)
        output << "It is confirmed that " << address
            << " depends on this passphrase." << std::endl;
    else
        output << BX_EC_LOCK_VERIFY_INVALID << std::endl;

    return console_result::okay;
}

