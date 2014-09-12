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
// #include "precompile.hpp"
#include <bitcoin/explorer/commands/fetch-header.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/header.hpp>
#include <bitcoin/explorer/server_client.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

static void handle_callback(callback_state& state, 
    const block_header_type& block_header)
{
    if (state.get_engine() == encoding_engine::native)
        state.output(header(block_header));
    else
        state.output(prop_tree(block_header));

    state.stop();
}

console_result fetch_header::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const size_t height = get_height_option();
    const hash_digest& hash = get_hash_option();
    const encoding& encoding = get_format_option();

    callback_state state(error, output, encoding);
    const auto handler = [&state](const std::error_code& code,
        const block_header_type& block_header)
    {
        if (!state.handle_error(code))
            handle_callback(state, block_header);
    };

    server_client client(*this);
    //auto& fullnode = client.get_fullnode();
    //state.start();
    //if (hash == null_hash)
    //    fullnode.blockchain.fetch_block_header(height, handler);
    //else
    //    fullnode.blockchain.fetch_block_header(hash, handler);
    //client.poll(state.stopped());

    return state.get_result();
}

