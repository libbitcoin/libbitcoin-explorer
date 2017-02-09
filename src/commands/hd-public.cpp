/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/hd-public.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>


namespace libbitcoin {
namespace explorer {
namespace commands {

console_result hd_public::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto hard = get_hard_option();
    const auto index = get_index_option();
    const auto private_version = get_secret_version_option();
    const auto public_version = get_public_version_option();
    const auto& key = get_hd_key_argument();

    const auto key_version = key.version();
    if (key_version != private_version && key_version != public_version)
    {
        output << "ERROR_VERSION" << std::endl;
        return console_result::failure;
    }

    if (hard && key_version != private_version)
    {
        error << BX_HD_PUBLIC_HARD_OPTION_CONFLICT << std::endl;
        return console_result::failure;
    }

    if (key_version == private_version)
    {
        const auto prefixes = bc::wallet::hd_private::to_prefixes(
            key.version(), public_version);

        // Derive the public key from new private key and the public version.
        const bc::wallet::hd_private private_key(key, prefixes);
        if (private_key)
        {
            static constexpr auto first = bc::wallet::hd_first_hardened_key;
            const auto position = hard ? first + index : index;

            const auto child_public_key = private_key.derive_public(position);
            if (child_public_key)
            {
                output << child_public_key << std::endl;
                return console_result::okay;
            }
        }
    }
    else
    {
        // Derive the public key from new private key and the public version.
        const bc::wallet::hd_public public_key(key, public_version);
        if (public_key)
        {
            const auto child_public_key = public_key.derive_public(index);
            if (child_public_key)
            {
                output << child_public_key << std::endl;
                return console_result::okay;
            }
        }
    }


    output << "ERROR_KEY" << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
