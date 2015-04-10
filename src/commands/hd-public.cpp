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

#include <bitcoin/explorer/commands/hd-public.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/primitives/hd_pub.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result hd_public::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto hard = get_hard_option();
    const auto index = get_index_option();
    const auto& key = get_hd_public_key_argument();

    bc::wallet::hd_public_key child_key;
    const bc::wallet::hd_public_key& public_key = key;
    const bc::wallet::hd_private_key& private_key = key;

    if (!private_key.valid() && hard)
    {
        error << BX_HD_PUBLIC_HARD_OPTION_CONFLICT << std::endl;
        return console_result::failure;
    }

    const auto position = if_else(hard, index + bc::wallet::first_hardened_key, index);

    if (private_key.valid())
        child_key = private_key.generate_public_key(position);
    else
        child_key = public_key.generate_public_key(position);

    output << hd_pub(child_key) << std::endl;
    return console_result::okay;
}
