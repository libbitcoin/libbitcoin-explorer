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
#include <bitcoin/explorer/commands/ec-to-witness.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result ec_to_witness::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& point = get_ec_public_key_argument();
    const auto& prefix = get_prefix_argument();

    if (witness_address::parse_prefix(prefix) !=
        witness_address::parse_result::valid)
    {
        output << BX_EC_TO_WITNESS_INVALID_PREFIX << std::endl;
        return console_result::failure;
    }

    const witness_address address(point, prefix);

    output << address << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
