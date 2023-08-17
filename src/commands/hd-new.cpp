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
#include <bitcoin/explorer/commands/hd-new.hpp>

#include <bitcoin/explorer/define.hpp>

// The BX_HD_NEW_INVALID_KEY condition is uncovered by test.
// This is because is not known what seed will produce an invalid key.
namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result hd_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto version = get_version_option();
    const data_chunk& entropy = get_entropy_argument();

    if (entropy.size() < minimum_seed_size)
    {
        error << BX_HD_NEW_SHORT_ENTROPY << std::endl;
        return console_result::failure;
    }

    // We require the private version, but public is unused here.
    const auto prefixes = wallet::hd_private::to_prefixes(version, 0);
    const wallet::hd_private private_key(entropy, prefixes);

    if (!private_key)
    {
        error << BX_HD_NEW_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << private_key << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
