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

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result ec_lock::invoke(std::ostream& output, std::ostream& error)
{
    // TODO: create primitives for intermediate and confirmation_code.
    // TODO: split into `ec-lock` and `secret-new`.
    // TODO: change `ec-lock-verify` to `secret-to-public`.
    // TODO: create new `intermediate` command.
    ///////////////////////////////////////////////////////////////////////////

    // bx ec-lock PASSPHRASE EC_PRIVATE_KEY[stdin] -> ENCRYPTED_PRIVATE_KEY
    const auto& secret = get_ec_private_key_argument();
    const auto& passphrase = get_passphrase_option();
    // bx ec-unlock PASSPHRASE ENCRYPTED_PRIVATE_KEY[stdin] -> EC_PRIVATE_KEY

    // bx intermediate SEED[stdin] LOT SEQUENCE
    // bx secret-new INTERMEDIATE SEED[stdin] --uncompressed -> 
    //     ENCRYPTED_PRIVATE_KEY:CONFIRMATION_CODE
    const data_chunk& intermediate_decoded = get_intermediate_option();
    const data_chunk& seed_buffer = get_seed_option();
    const auto uncompressed = get_uncompressed_option();
    // bx secret-to-public PASSPHRASE CONFIRMATION_CODE -> EC_PUBLIC_KEY

    if (passphrase.empty() && intermediate_decoded.empty())
    {
        error << BX_EC_LOCK_MODE_REQUIRED << std::endl;
        return console_result::failure;
    }

    if (!passphrase.empty() && !intermediate_decoded.empty())
    {
        error << BX_EC_LOCK_MODE_CONFLICT << std::endl;
        return console_result::failure;
    }

    // passphrase mode
    ///////////////////////////////////////////////////////////////////////////

    if (!passphrase.empty())
    {
        if (!intermediate_decoded.empty())
        {
            error << BX_EC_LOCK_INTERMEDIATE_CONFLICT << std::endl;
            return console_result::failure;
        }

        if (!seed_buffer.empty())
        {
            error << BX_EC_LOCK_SEED_CONFLICT << std::endl;
            return console_result::failure;
        }

#ifdef WITH_ICU
        const auto encrypted_key = bip38::lock_secret(secret, passphrase,
            !uncompressed);

        output << encode_base58(encrypted_key) << std::endl;
        return console_result::okay;
#else
        error << BX_EC_LOCK_PASSPHRASE_REQUIRES_ICU << std::endl;
        return console_result::failure;
#endif
    }

    // intermediate mode
    ///////////////////////////////////////////////////////////////////////////

    if (intermediate_decoded.size() != bip38::intermediate_decoded_size)
    {
        error << BX_EC_LOCK_INTERMEDIATE_LENGTH_INVALID << std::endl;
        return console_result::failure;
    }

    bip38::intermediate intermediate;
    std::copy(intermediate_decoded.begin(), intermediate_decoded.end(),
        intermediate.begin());

    if (seed_buffer.size() < bip38::seed_size)
    {
        error << BX_EC_LOCK_SHORT_SEED << std::endl;
        return console_result::failure;
    }

    // Allow excess seed, just truncate the unused bytes.
    bip38::seed seed;
    std::copy(seed_buffer.begin(), seed_buffer.begin() + bip38::seed_size,
        seed.begin());

    bip38::confirmation_code confirmation_code;
    const auto encrypted_key = bip38::lock_intermediate(intermediate, seed,
        confirmation_code, !uncompressed);

    // TODO: use complex output (?)
    output << encode_base58(encrypted_key) << std::endl;
    output << encode_base58(confirmation_code) << std::endl;
    return console_result::okay;
}
