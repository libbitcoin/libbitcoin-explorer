/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include "precompile.hpp"
#include <explorer/commands/address-validate.hpp>

#include <iostream>
#include <boost/program_options.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/address.hpp>

using namespace po;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

// 100% coverage by line, loc ready.
console_result address_validate::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& token = get_bitcoin_address_argument();

    // TESTNET VERSION REQUIRES RECOMPILE

    // The value is bound to a string so that we can handle validation here
    // instead of in the deprimitive.

    try
    {
        const address bitcoin_address(token);
        output << bitcoin_address << std::endl;
        return console_result::okay;
    }
    catch (invalid_option_value&)
    {
        // We do not return a failure here, as this is a validity test.
        output << BX_ADDRESS_VALIDATE_INVALID_ADDRESS << std::endl;
        return console_result::invalid;
    }
}