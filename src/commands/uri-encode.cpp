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

#include <bitcoin/explorer/commands/uri-encode.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;

 console_result uri_encode::invoke(std::ostream& output, std::ostream& error)
 {
     // Bound parameters.
     const auto& amount = get_amount_option();
     const auto& label = get_label_option();
     const auto& message = get_message_option();
     const auto& request = get_request_option();
     const auto& stealth = get_stealth_option();
     const auto& address = get_bitcoin_address_argument();

     if (stealth && address)
     {
         error << BX_URI_ENCODE_ADDRESS_CONFLICT << std::endl;
         return console_result::failure;
     }

     bc::wallet::uri_writer writer;

     if (stealth)
         writer.write_address(stealth);

     if (address)
         writer.write_address(address);

     if (amount > 0)
         writer.write_amount(amount);

     if (!label.empty())
         writer.write_label(label);

     if (!message.empty())
         writer.write_message(message);

     const auto uri = request.to_string();
     if (!uri.empty())
         writer.write_r(uri);

     output << writer.string() << std::endl;
     return console_result::okay;
 }
