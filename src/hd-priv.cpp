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
#include <iostream>
#include <wallet/wallet.hpp>
#include <sx/command/hd-priv.hpp>
#include <sx/utility/console.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// 100% coverage by line, loc ready.
console_result hd_priv::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const auto hard = get_hard_option();
    auto secret = get_secret_argument();
    auto index = get_index_argument();

    if (hard)
        index += first_hardened_key;

    hd_private_key private_key = secret;
    const auto child_key = private_key.generate_private_key(index);
    if (!child_key.valid())
    {
        cerr << SX_HD_PRIV_DERIVATION_ERROR << std::endl;
        return console_result::failure;
    }

    output << hd_private(child_key) << std::endl;
    return console_result::okay;
}

