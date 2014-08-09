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
#include <sx/command/fetch-confirmations.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/define.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/utility/callback_args.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;

// TODO: use parse tree?
static void handle_callback(callback_args& args, const index_list& confirmations)
{
    for (const auto& confirmation: confirmations)
        args.output() << confirmation << std::endl;
}

console_result fetch_confirmations::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& transactions = get_transactions_argument();
    HANDLE_MULTIPLE_NOT_IMPLEMENTED(transactions, error);
    const transaction_type& tx = transactions.front();

    callback_args args(error, output);
    const auto handler = [&args](const std::error_code& code,
        const index_list& unconfirmed)
    {
        handle_error(args, code);
        handle_callback(args, unconfirmed);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.transaction_pool.validate(tx, handler);
    client.poll(args.stopped());

    return args.result();
}