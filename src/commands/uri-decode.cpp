/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/uri-decode.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

 using namespace bc::explorer;
 using namespace bc::explorer::commands;

 console_result uri_decode::invoke(std::ostream& output, std::ostream& error)
 {
     // Bound parameters.
     const auto& encoding = get_format_option();
     const auto& uri = get_uri_argument();

     // The uri primitive type is not currently restricted to bitcoin uris.
     if (!starts_with(uri, "bitcoin:"))
     {
         error << BX_URI_DECODE_NOT_BITCOIN << std::endl;
         return console_result::failure;
     }
     
     write_stream(output, prop_tree(uri), encoding);
     return console_result::okay;
 }
