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
#include <bitcoin/explorer/commands/address-embed.hpp>

#include <iostream>
#include <utility>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::chain;
using namespace bc::system::wallet;

console_result address_embed::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const data_chunk& data = get_data_argument();
    const auto version = get_version_option();

    // Create script from hash of data.
    const auto ops = script::to_pay_key_hash_pattern(ripemd160_hash(data));
    const script script(ops);

    // Make ripemd hash of serialized script.
    const auto hash = ripemd160_hash(script.to_data(false));

    // Make address (money sent here is lost, unless data is public key).
    output << payment_address(hash, version) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
