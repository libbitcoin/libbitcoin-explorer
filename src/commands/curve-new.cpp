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

#include <bitcoin/explorer/commands/curve-new.hpp>

#include <algorithm>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

// A Base85 key encoding containing a hash sign cannot be used in a config file.
static bool encode(std::string& out, const x25519::key& key) NOEXCEPT
{
    return encode_base85(out, key) && !contains(out, '#');
}

console_result curve_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const data_chunk& entropy = get_entropy_argument();

    if (entropy.size() < x25519::key_size)
    {
        error << BX_CURVE_NEW_SHORT_ENTROPY << std::endl;
        return console_result::failure;
    }

    x25519::key secret{};
    x25519::key point{};
    std::copy_n(entropy.begin(), x25519::key_size, secret.begin());

    std::string private_key{};
    std::string public_key{};
    if (!x25519::multiply(point, secret) ||
        !encode(private_key, secret) ||
        !encode(public_key, point))
    {
        error << BX_CURVE_NEW_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << private_key << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
