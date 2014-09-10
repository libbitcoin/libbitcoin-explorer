/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include "precompile.hpp"
#include <explorer/commands/fetch-stealth.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <explorer/callback_state.hpp>
#include <explorer/define.hpp>
#include <explorer/obelisk_client.hpp>
#include <explorer/prop_tree.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

// Write out the transaction hashes of *potential* matches.
static void handle_prefix_callback(callback_state& state, 
    const stealth_prefix& prefix, const blockchain::stealth_list& row_list)
{
    state.output(prop_tree(prefix, row_list));

    // This call has been handled.
    --state;
}

console_result fetch_stealth::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto height = get_height_option();
    const auto& prefixes = get_prefixs_argument();
    const auto& encoding = get_format_option();

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    callback_state state(error, output, encoding);

    for (const stealth_prefix& prefix: prefixes)
    {
        const auto prefix_handler = [&state, &prefix](
            const std::error_code& code,
            const blockchain::stealth_list& stealth_results)
        {
            if (!state.handle_error(code))
                handle_prefix_callback(state, prefix, stealth_results);
        };

        ++state;
        fullnode.blockchain.fetch_stealth(prefix,
            std::bind(prefix_handler, ph::_1, ph::_2), height);
    }

    client.poll(state.stopped());

    return state.get_result();
}

