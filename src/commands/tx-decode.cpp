/**
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
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
#include <explorer/commands/tx-decode.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/prop_tree.hpp>
#include <explorer/primitives/transaction.hpp>
#include <explorer/utility/utility.hpp>

using namespace bc;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

console_result tx_decode::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& transactions = get_transactions_argument();

    if (encoding == encoding_engine::native)
    {
        for (const auto& tx: transactions)
            output << transaction(tx) << std::endl;
    }
    else
    {
        const auto tree = prop_tree(transactions);
        write_stream(output, tree, encoding);
    }

    return console_result::okay;
}