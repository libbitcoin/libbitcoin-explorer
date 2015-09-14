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

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;
using namespace bc::wallet;

console_result token_new::invoke(std::ostream& output, std::ostream& error)
{
#ifdef WITH_ICU
    const auto lot = get_lot_option();
    const auto sequence = get_sequence_option();
    const auto& passphrase = get_passphrase_argument();
    const data_chunk& salt = get_salt_argument();

    if (salt.size() < ek_salt_size)
    {
        error << BX_TOKEN_NEW_SHORT_SALT << std::endl;
        return console_result::failure;
    }

    if (lot > ek_max_lot)
    {
        error << BX_TOKEN_NEW_MAXIMUM_LOT << std::endl;
        return console_result::failure;
    }

    if (sequence > ek_max_sequence)
    {
        error << BX_TOKEN_NEW_MAXIMUM_SEQUENCE << std::endl;
        return console_result::failure;
    }

    config::ek_token token;
    if (lot == 0 && sequence == 0 && salt.size() >= ek_entropy_size)
    {
        ek_entropy bytes;
        std::copy(salt.begin(), salt.begin() + bytes.size(), bytes.begin());
        create_token(token.data(), passphrase, bytes);
    }
    else
    {
        ek_salt bytes;
        std::copy(salt.begin(), salt.begin() + bytes.size(), bytes.begin());
        create_token(token.data(), passphrase, bytes, lot, sequence);
    }

    output << token << std::endl;
    return console_result::okay;
#else
    error << BX_TOKEN_NEW_REQUIRES_ICU << std::endl;
    return console_result::failure;
#endif
}
