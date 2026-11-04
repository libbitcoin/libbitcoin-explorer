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
#include <bitcoin/explorer/commands/slip39-split.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result slip39_split::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& configured = get_groups_option();
    const data_chunk& secret = get_secret_option();
    const auto threshold = get_threshold_option();
    const auto identifier = get_identifier_option();
    const auto exponent = get_exponent_option();
    const auto extendable = !get_unextendable_option();
    const auto& passphrase = get_passphrase_option();
    const data_chunk& entropy = get_entropy_argument();

    if (!slip39::is_valid_entropy_size(secret.size()))
    {
        error << BX_SLIP39_SPLIT_INVALID_SECRET << std::endl;
        return console_result::failure;
    }

    const slip39::groups groups(configured.begin(), configured.end());
    if (!slip39::is_valid_grouping(threshold, groups))
    {
        error << BX_SLIP39_SPLIT_INVALID_GROUPS << std::endl;
        return console_result::failure;
    }

    if (identifier > maximum_slip39_identifier)
    {
        error << BX_SLIP39_SPLIT_INVALID_IDENTIFIER << std::endl;
        return console_result::failure;
    }

    if (exponent > maximum_slip39_exponent)
    {
        error << BX_SLIP39_SPLIT_INVALID_EXPONENT << std::endl;
        return console_result::failure;
    }

    if (!slip39::is_valid_passphrase(passphrase))
    {
        error << BX_SLIP39_SPLIT_INVALID_PASSPHRASE << std::endl;
        return console_result::failure;
    }

    const auto size = slip39::entropy_size(secret.size(), threshold, groups);
    if (entropy.size() != size)
    {
        error << BX_SLIP39_SPLIT_INVALID_ENTROPY_SIZE " " << size << std::endl;
        return console_result::failure;
    }

    const auto shares = slip39::to_shares(secret, groups, threshold, entropy,
        identifier, extendable, exponent, passphrase);

    for (const auto& share: shares)
        output << share.sentence() << std::endl;

    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
