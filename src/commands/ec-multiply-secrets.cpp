/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/ec-multiply-secrets.hpp>

#include <iostream>
#include <iterator>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::config;

console_result ec_multiply_secrets::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& secrets = get_secrets_argument();

    if (secrets.empty())
    {
        output << base16(null_hash) << std::endl;
        return console_result::okay;
    }

    ec_secret product(secrets.front());

    for (auto secret = std::next(secrets.begin()); secret != secrets.end(); ++secret)
    {
        // Elliptic curve function (INTEGER * INTEGER) % curve-order.
        if (!system::ec_multiply(product, *secret))
        {
            error << BX_EC_MULITPLY_SECRETS_OUT_OF_RANGE << std::endl;
            return console_result::failure;
        }
    }

    output << base16(product) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
