/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <sx/command/hd-priv.hpp>

#include <iostream>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hd_private.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// 100% coverage by line, loc ready.
console_result hd_priv::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto hard = get_hard_option();
    const auto index = get_index_option();
    const hd_private_key& secret = get_secret_argument();

    const auto position = if_else(hard, index + first_hardened_key, index);
    const auto child_key = secret.generate_private_key(position);

    output << hd_private(child_key) << std::endl;
    return console_result::okay;
}