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
#include <bitcoin/explorer/primitives/base58.hpp>
#include <bitcoin/explorer/primitives/ec_private.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result ec_lock_verify::invoke(std::ostream& output,
    std::ostream& error)
{
#ifdef WITH_ICU
    const auto& passphrase = get_passphrase_argument();
    const data_chunk& code_decoded = get_confirmation_code_argument();

    if (code_decoded.size() != bip38::confirmation_code_decoded_size)
    {
        error << BX_EC_LOCK_VERIFY_CONFIRMATION_LENGTH_INVALID << std::endl;
        return console_result::failure;
    }

    bip38::confirmation_code code;
    std::copy(code_decoded.begin(), code_decoded.end(), code.begin());

    bc::wallet::payment_address address;
    const auto confirmed = bip38::lock_verify(code, passphrase, address);
    if (confirmed)
        output << BX_EC_LOCK_VERIFY_VALID << std::endl;
    else
        output << BX_EC_LOCK_VERIFY_INVALID << std::endl;

    return console_result::okay;
#else
    error << BX_EC_LOCK_VERIFY_PASSPHRASE_REQUIRES_ICU << std::endl;
    return console_result::failure;
#endif
}

