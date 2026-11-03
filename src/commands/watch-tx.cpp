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

#include <bitcoin/explorer/commands/watch-tx.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/client.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result watch_tx::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto duration = get_duration_option();
    const hash_digest& hash = get_hash_argument();
    const auto expected = encode_hash(hash);
    client server(*this, get_server_url_argument());

    auto observed = false;
    const auto notify = [&](const json::value& value) NOEXCEPT
    {
        const auto text = value.if_string();
        observed = text && (std::string_view(*text) == expected);
        return !observed;
    };

    if (!server.subscribe(error, "tx/subscribe", duration, notify))
        return console_result::failure;

    if (!observed)
    {
        error << BX_WATCH_TX_TIMEOUT << std::endl;
        return console_result::failure;
    }

    json::value response{};
    if (!server.fetch(response, error, "tx/" + expected))
        return console_result::failure;

    write_stream(output, response);
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
