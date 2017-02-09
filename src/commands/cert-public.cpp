/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/cert-public.hpp>

#include <bitcoin/protocol.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::config;
using namespace bc::protocol;

console_result cert_public::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& private_key = get_private_key_argument();

    // Generate the public key from the private key (if valid).
    zmq::certificate certificate(private_key);

    // Certificate generation uses null_hash key as a sentinel for generation
    // of a new keypair, so it must be excluded here if the user entered it.
    if (!private_key || !certificate)
    {
        error << BX_CERT_PUBLIC_INVALID << std::endl;
        return console_result::failure;
    }

    output << certificate.public_key() << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
