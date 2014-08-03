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
#include <sx/command/validtx.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;

// TODO: this should be a member of sx::extensions::monitor,
// otherwise concurrent test execution will collide on shared state.
static bool stopped;
static console_result result;

// TODO: stopped should be passed here via closure
// or by converting this to a member function.
static void valid_tx(const std::error_code& error, 
    const index_list& unconfirmed)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
        stopped = true;
        return;
    }

    std::cout << error.message() << std::endl;
    for (size_t unconfirmed_index: unconfirmed)
        std::cout << "  Unconfirmed: " << unconfirmed_index << std::endl;
}

console_result validtx::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto& transactions = get_transactions_argument();

    // TODO: remove this hack which requires one element.
    const transaction_type& tx = transactions.front();

    stopped = false;
    result = console_result::okay;

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.transaction_pool.validate(tx, valid_tx);
    client.poll(stopped);

    return result;
}

