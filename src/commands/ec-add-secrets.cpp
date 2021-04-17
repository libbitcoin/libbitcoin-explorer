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
#include <bitcoin/explorer/commands/ec-add-secrets.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result ec_add_secrets::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& secrets = get_secrets_argument();

    if (secrets.empty())
    {
        output << encode_base16(null_hash) << std::endl;
        return console_result::okay;
    }

    // Secrets can be invalid, this should be handled.
    // The test cases are providing base16 but WIF is expected.
    // ec_private reads/writes WIF but ec_public reads/writes base16.
    // This should probably be rationalized at some point.
    // This would also simplify out serialization, vs. encode_based16(ec_secret).
    
    // TODO: create a wallet::wif class and use this for wif serialialization
    // and deserialization. Create a constructor to take this in ec_private and
    // then change string in/out in ec_private handle base16, for consistency with
    // ec_public, and to provide a way to convert secrets using classes. Provide
    // an ec_private cast override for the wif class. Model this wif after hd_public
    // and private. Could provide wif construction for hd and ek classes, but this
    // isn't necessary, since wif will cast to ec_secret, which they shold already
    // accept.

    // TODO: replace all >> BOOST_THROW_EXCEPTION in ::system so they are not
    // bypassed in debug builds. Move using definition into bc namespace.

    // TODO: the test cases don't use >>, so they can introduce invalid objects.
    // So all objects need to be tested for validity in bx invoke handlers,
    // as these can be used independently via setters just as the test cases.
    // The setters shouldn't throw, but an invalid paramter could cause
    // premature termination. This would require consistent bool() operators.
    // Probbably better to demonstrate validity testing in the handlers.

    // TODO: figure out why invalidity is causing a memory access violation, as
    // this should not be allowed in any case.

    ec_secret sum(secrets.front());

    for (auto secret = std::next(secrets.begin()); secret != secrets.end(); ++secret)
    {
        // Elliptic curve function (INTEGER + INTEGER) % curve-order.
        if (!system::ec_add(sum, *secret))
        {
            error << BX_EC_ADD_SECRETS_OUT_OF_RANGE << std::endl;
            return console_result::failure;
        }
    }

    output << encode_base16(sum) << std::endl;
    return console_result::okay;
}


} //namespace commands
} //namespace explorer
} //namespace libbitcoin
