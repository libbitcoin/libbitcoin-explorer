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

console_result ec_lock::invoke(std::ostream& output, std::ostream& error)
{
    const auto& secret = get_ec_private_key_argument();
    const auto& passphrase = get_passphrase_argument();
    const auto& intermediate = get_intermediate_argument();
    const auto& seed = get_seed_argument();
    const auto& show_confirm = get_confirm_argument();
    const bool& use_compression = get_compress_argument();

    constexpr auto bip38_intermediate_required_length = 53;
    constexpr auto bip38_seed_required_length = 24;

    if (!verify_private_key(secret))
    {
        error << BX_EC_LOCK_PRIVKEY_LENGTH_INVALID << std::endl;
        return console_result::failure;
    }

    data_chunk _seed = seed;
    data_chunk _intermediate = intermediate;

    if (passphrase.size() && (_intermediate.size() || _seed.size()))
    {
        error << BX_EC_LOCK_MODE_INCORRECT << std::endl;
        return console_result::failure;
    }

    if (passphrase.size() && _intermediate.size())
    {
        error << BX_EC_LOCK_MODE_INCORRECT << std::endl;
        return console_result::failure;
    }

    if (passphrase.size() && _seed.size())
    {
        error << BX_EC_LOCK_SEED_NOT_REQUIRED << std::endl;
        return console_result::failure;
    }

    if (_intermediate.size() &&
       (_intermediate.size() != bip38_intermediate_required_length))
    {
        error << "intermediate size is " << _intermediate.size() << std::endl;
        error << BX_EC_LOCK_INTERMEDIATE_LENGTH_INVALID << std::endl;
        return console_result::failure;
    }

    if (_intermediate.size() &&
        !(_seed.size() == bip38_seed_required_length))
    {
        error << "seed size is " << _seed.size() << std::endl;
        error << BX_EC_LOCK_SEED_LENGTH_INVALID << std::endl;
        return console_result::failure;
    }

    if (_intermediate.size() && _seed.size() &&
        (passphrase.size() == 0))
    {
        data_chunk confirmation;
        const auto locked = bip38_lock_intermediate(
            intermediate, seed, confirmation, use_compression);
        output << encode_base58(locked) << std::endl;

        if (show_confirm)
            output << encode_base58(confirmation) << std::endl;
    }
    else
    {
#ifdef WITH_ICU
        const auto locked = bip38_lock_secret(
            secret, passphrase, use_compression);
        output << encode_base58(locked) << std::endl;
#else
        error << BX_EC_LOCK_USING_PASSPHRASE_UNSUPPORTED << std::endl;
        return console_result::failure;
#endif
    }
    return console_result::okay;
}

