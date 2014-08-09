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
#include <sx/command/header-decode.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <boost/format.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

// TODO: use ptree.
// This is NOT localizable.
static const char* json_format =
"{\n"
"   \"bits\": \"%1%\",\n"
"   \"hash\": \"%2%\",\n"
"   \"merkle\": \"%3%\",\n"
"   \"nonce\": \"%4%\"\n"
"   \"previous_block_hash\": \"%5%\",\n"
"   \"timestamp\": \"%6%\"\n"
"   \"version\": \"%7%\"\n"
"}";

console_result header_decode::invoke(std::ostream& output, std::ostream& error)
{
    const auto json = get_json_option();
    const auto& headers = get_headers_argument();

    const auto format = if_else(json, json_format, SX_HEADER_DECODE_OUTPUT);

    for (const block_header_type& header: headers)
        output << boost::format(format) % header.bits %
            hex(hash_block_header(header)) % hex(header.merkle) % header.nonce %
            hex(header.previous_block_hash) % header.timestamp % header.version 
            << std::endl;

    return console_result::okay;
}