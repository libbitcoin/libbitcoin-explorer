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
#include "precompile.hpp"
#include <sx/command/address-validate.hpp>

#include <iostream>
#include <sx/define.hpp>

using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// 100% coverage by line, loc ready.
console_result address_validate::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& addresses = get_bitcoin_addresss_argument();

    // TESTNET VERSION REQUIRES RECOMPILE
    // If any address is not valid the deserializer will throw.
    // TODO: read as hexcode, validate here and provide localized message
    // for each address. See:
    // SX_INPUT_VALIDATE_INDEX_VALID_SIGNATURE
    // SX_INPUT_VALIDATE_INDEX_INVALID_SIGNATURE

    return console_result::okay;
}