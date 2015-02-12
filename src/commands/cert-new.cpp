/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

#include <boost/format.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/obelisk_client.hpp>
#include <bitcoin/explorer/utility.hpp>
#include <czmq++/czmqpp.hpp>

using namespace czmqpp;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;
using boost::format;

// CZMQ only has a file system interface, otherwise would send to stdout.
console_result cert_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& private_cert = get_private_cert_argument();
    const auto& metadata = get_metadatas_option();

    // Create a new Curve ZMQ certificate.
    auto cert = certificate(zcert_new());

    // Add optional name-value pairs metadata to certificate.
    // These will be coppied to the public certificate by cert-public.
    for (const auto pair: split_pairs(metadata))
        cert.set_meta(pair.first, pair.second);

    // The directory must exist, the file must not.
    // Export the PRIVATE certificate to the specified file.
    if (exists(private_cert) || 
        cert.save_secret(private_cert.generic_string()) != zmq_success)
    {
        error << format(BX_CERT_NEW_SAVE_FAIL) % private_cert << std::endl;
        return console_result::failure;
    }

    return console_result::okay;
}
