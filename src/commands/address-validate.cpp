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

#include <bitcoin/explorer/commands/address-validate.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/address.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result address_validate::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& token = get_payment_address_argument();

    // The address is bound to a string so that we can handle validation here
    // instead of in the primitive.

    // TESTNET VERSION REQUIRES RECOMPILE

    bc::wallet::payment_address pay_address;
    if (!pay_address.from_string(token))
    {
        // We do not return a failure here, as this is a validity test.
        output << BX_ADDRESS_VALIDATE_INVALID_ADDRESS << std::endl;
        return console_result::invalid;
    }

    output << BX_ADDRESS_VALIDATE_VALID_ADDRESS << std::endl;
    return console_result::okay;
}
