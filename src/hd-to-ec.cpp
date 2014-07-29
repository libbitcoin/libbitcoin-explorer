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
#include <sx/command/hd-to-ec.hpp>

#include <wallet/wallet.hpp>
#include <sx/serializer/address.hpp>
#include <sx/utility/utility.hpp>

using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result hd_to_ec::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const auto key = get_key_argument();

    hd_public_key child_key;
    const hd_public_key& public_key = key;
    const hd_private_key& private_key = key;

    if (private_key.valid())
        output << ec_private(private_key) << std::endl;
    else
        output << ec_public(public_key) << std::endl;

    return console_result::okay;
}