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
#include <bitcoin/explorer/commands/noise-new.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result noise_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const data_chunk& entropy = get_entropy_argument();

    if (entropy.size() < ec_secret_size)
    {
        error << BX_NOISE_NEW_SHORT_ENTROPY << std::endl;
        return console_result::failure;
    }

    const auto secret = data_slice{ entropy }.to_array<ec_secret_size>();
    if (!verify_secret(secret))
    {
        error << BX_NOISE_NEW_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << system::config::base58check{ to_chunk(secret) } << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
