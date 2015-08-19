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

#include <bitcoin/explorer/commands/ec-unlock.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/ec_private.hpp>

using namespace bc;
using namespace bc::bip38;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result ec_unlock::invoke(std::ostream& output, std::ostream& error)
{
    const auto& secret = get_secret_argument();
    const auto& passphrase = get_passphrase_argument();

#ifdef WITH_ICU
    const auto unlocked = bip38_unlock_secret(
        base58(secret), passphrase);

    if (!verify_private_key(unlocked))
    {
        error << BX_EC_UNLOCK_FAILURE << std::endl;
        return console_result::failure;
    }

    output << encode_base16(unlocked) << std::endl;
    return console_result::okay;
#else
    error << BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED << std::endl;
    return console_result::failure;
#endif
}
