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
#include <bitcoin/explorer/commands/token-new.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/ek_token.hpp>

using namespace bc;
using namespace bc::bip38;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result token_new::invoke(std::ostream& output, std::ostream& error)
{
    const auto lot = get_lot_option();
    const auto sequence = get_sequence_option();
    const auto& passphrase = get_passphrase_argument();
    const data_chunk& salt = get_salt_argument();

#ifndef WITH_ICU
    error << BX_TOKEN_NEW_REQUIRES_ICU << std::endl;
    return console_result::failure;
#endif
    
    if (salt.size() < salt_size)
    {
        error << BX_TOKEN_NEW_SHORT_SALT << std::endl;
        return console_result::failure;
    }

    if (lot > max_token_lot)
    {
        error << BX_TOKEN_NEW_MAXIMUM_LOT << std::endl;
        return console_result::failure;
    }

    if (sequence > max_token_sequence)
    {
        error << BX_TOKEN_NEW_MAXIMUM_SEQUENCE << std::endl;
        return console_result::failure;
    }

    bip38::salt bytes;
    std::copy(salt.begin(), salt.begin() + salt_size, bytes.begin());

    ek_token token;
    create_token(token.data(), passphrase, bytes, lot, sequence);

    output << token << std::endl;
    return console_result::okay;
}
