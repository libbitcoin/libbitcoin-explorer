/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/tx-sign.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>


namespace libbitcoin {
namespace explorer {
namespace commands {

console_result tx_sign::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    //const auto& transactions = get_transactions_argument();

    //for (const tx_type& tx: transactions)
    //    /* sign */;

    error << BX_TX_SIGN_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
