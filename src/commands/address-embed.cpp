/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/address-embed.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;
using namespace bc::wallet;

console_result address_embed::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& data = get_data_argument();
    const auto& version = get_version_option();

    // Create script from hash of data.
    const auto hashed = ripemd160_hash(data);
    const auto ops = chain::operation::to_pay_key_hash_pattern(hashed);
    const auto script = chain::script{ ops };

    // Make ripemd hash of serialized script.
    const auto hash = ripemd160_hash(script.to_data(false));
    
    // Make address (money sent here is lost forever).
    output << payment_address(hash, version) << std::endl;
    return console_result::okay;
}
