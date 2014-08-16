/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <sx/command/fetch-tx-index.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/callback_state.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/prop_tree.hpp>
#include <sx/serializer/base16.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static void handle_callback(callback_state& state, const bc::hash_digest& hash,
    size_t height, size_t index)
{
    // TODO: make ptree.
    state.output(boost::format("[%1%] Height: %2% Index: %3%") % base16(hash) %
        height % index);

    --state;
}

console_result fetch_tx_index::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& hashes = get_hashs_argument();
    const auto& encoding = get_format_option();

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    callback_state state(error, output, encoding);

    for (const auto& hash: hashes)
    {
        const auto handler = [&state, &hash](
            const std::error_code& code, size_t height, size_t index)
        {
            if (!state.handle_error(code))
                handle_callback(state, hash, height, index);
        };

        fullnode.blockchain.fetch_transaction_index(hash, handler);
        ++state;
    }

    client.poll(state.stopped());

    return state.get_result();
}

