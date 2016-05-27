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
#include <bitcoin/explorer/commands/cert-new.hpp>

#include <bitcoin/protocol.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace bc;
using namespace bc::config;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::protocol;

console_result cert_new::invoke(std::ostream& output, std::ostream& error)
{
    // TODO: update settings implementation so '#' character can be allowed.
    // BUGBUG: Removal of '#' by certificate reduces keyspace/security.

    // Create a new Curve ZMQ certificate.
    zmq::certificate certificate;

    if (!certificate)
    {
        error << BX_CERT_NEW_FAILURE << std::endl;
        return console_result::failure;
    }

    output << certificate.private_key() << std::endl;
    return console_result::okay;
}
