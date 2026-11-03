/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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

#include <algorithm>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result cert_public::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const data_chunk& secret = get_private_key_argument();

    x25519::key scalar{};
    x25519::key point{};
    std::string public_key{};
    if (secret.size() != x25519::key_size)
    {
        error << BX_CERT_PUBLIC_INVALID << std::endl;
        return console_result::failure;
    }

    std::copy_n(secret.begin(), x25519::key_size, scalar.begin());
    if (!x25519::multiply(point, scalar) || !encode_base85(public_key, point))
    {
        error << BX_CERT_PUBLIC_INVALID << std::endl;
        return console_result::failure;
    }

    output << public_key << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
