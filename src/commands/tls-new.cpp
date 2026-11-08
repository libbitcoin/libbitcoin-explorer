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

#include <bitcoin/explorer/commands/tls-new.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result tls_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const data_chunk& entropy = get_entropy_argument();

    x509::secret secret{};
    if (entropy.size() < secret.size())
    {
        error << BX_TLS_NEW_SHORT_ENTROPY << std::endl;
        return console_result::failure;
    }

    std::copy_n(entropy.begin(), secret.size(), secret.begin());
    const auto key = x509::encode_private_key(secret);
    if (key.empty())
    {
        error << BX_TLS_NEW_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << key;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
