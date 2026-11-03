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

#include <bitcoin/explorer/commands/fetch-utxo.hpp>

#include <format>
#include <algorithm>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/client.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

using selection = explorer::config::algorithm::type;

static uint64_t value_of(const json::value& unspent) NOEXCEPT
{
    const auto object = unspent.if_object();
    if (!object)
        return 0;

    const auto value = object->if_contains("value");
    if (!value)
        return 0;

    std::error_code ec{};
    const auto satoshi = value->to_number<uint64_t>(ec);
    return ec ? 0 : satoshi;
}

// Greedy takes the largest outputs until the amount is covered, individual
// takes the smallest single output that covers it.
static bool select(json::array& out, const json::array& unspent,
    uint64_t satoshi, selection algorithm) NOEXCEPT
{
    json::array sorted(unspent);
    std::sort(sorted.begin(), sorted.end(),
        [](const json::value& left, const json::value& right) NOEXCEPT
        {
            return value_of(left) > value_of(right);
        });

    if (algorithm == selection::individual)
    {
        for (const auto& output: sorted)
        {
            if (value_of(output) < satoshi)
                break;

            out = json::array{ output };
        }

        return !out.empty();
    }

    uint64_t sum{};
    for (const auto& output: sorted)
    {
        if (sum >= satoshi)
            break;

        sum = ceilinged_add(sum, value_of(output));
        out.push_back(output);
    }

    return sum >= satoshi;
}

console_result fetch_utxo::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& argument = get_server_url_argument();
    const auto& url = is_zero(argument.port()) ?
        get_server_url_setting() : argument;
    const selection algorithm = get_algorithm_option();
    const auto satoshi = get_satoshi_argument();
    const hash_digest& hash = get_hash_argument();
    const auto path = "address/" + encode_hash(hash);

    client server(url, get_server_connect_retries_setting(),
        get_server_connect_timeout_seconds_setting());

    json::value response{};
    std::string message{};

    if (!server.get(response, message, path))
    {
        error << std::format(BX_FETCH_UTXO_FAILED, message) << std::endl;
        return console_result::failure;
    }

    const auto unspent = response.if_array();
    if (!unspent)
    {
        error << std::format(BX_FETCH_UTXO_FAILED, "unexpected response")
            << std::endl;
        return console_result::failure;
    }

    json::array selected{};
    if (!select(selected, *unspent, satoshi, algorithm))
    {
        error << BX_FETCH_UTXO_INSUFFICIENT << std::endl;
        return console_result::failure;
    }

    write_stream(output, selected);
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
