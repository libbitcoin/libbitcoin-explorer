/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/fetch-header.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/client.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result fetch_header::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& argument = get_server_url_argument();
    const auto& url = is_zero(argument.port()) ?
        get_server_url_setting() : argument;
    const hash_digest& hash = get_hash_option();
    const auto height = get_height_option();

    const auto path = hash == null_hash ?
        "block/height/" + serialize(height) + "/header" :
        "block/hash/" + encode_hash(hash) + "/header";

    client server(url, get_server_connect_retries_setting(),
        get_server_connect_timeout_seconds_setting());

    json::value response{};
    std::string message{};

    if (!server.get(response, message, path))
    {
        error << std::format(BX_FETCH_HEADER_FAILED, message) << std::endl;
        return console_result::failure;
    }

    write_stream(output, response);
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
