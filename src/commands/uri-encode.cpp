/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/uri-encode.hpp>

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;

 console_result uri_encode::invoke(std::ostream& output, std::ostream& error)
 {
     // Bound parameters.
     const auto& amount = get_amount_option();
     const auto& label = get_label_option();
     const auto& message = get_message_option();
     const auto& request = get_request_option();
     const std::string& address = get_address_argument();

     bitcoin_uri uri;

     if (!address.empty())
         uri.set_address(address);

     if (amount > 0)
         uri.set_amount(amount);

     if (!label.empty())
         uri.set_label(label);

     if (!message.empty())
         uri.set_message(message);

     if (request)
         uri.set_r(request.to_string());

     output << uri.encoded() << std::endl;
     return console_result::okay;
 }

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
