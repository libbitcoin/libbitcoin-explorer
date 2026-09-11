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
#include <bitcoin/explorer/json.hpp>

#include <string>
#include <boost/json.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {

using namespace bc::system;
using namespace boost::json;

// Settings keys are dot-delimited section paths.
static void put_path(object& out, const std::string& path,
    const std::string& setting) NOEXCEPT
{
    const auto point = path.find('.');

    if (point == std::string::npos)
    {
        out[path] = setting;
        return;
    }

    auto& section = out[path.substr(0, point)];

    if (!section.is_object())
        section.emplace_object();

    put_path(section.get_object(), path.substr(add1(point)), setting);
}

value to_json(const settings_list& settings) NOEXCEPT
{
    object list;

    for (const auto& setting: settings)
        put_path(list, setting.first, setting.second);

    return object{ { "settings", std::move(list) } };
}

value to_json(const wallet::bitcoin_uri& uri) NOEXCEPT
{
    object properties;

    if (!uri.address().empty())
        properties["address"] = uri.address();

    if (!is_zero(uri.amount()))
        properties["amount"] = uri.amount();

    if (!uri.label().empty())
        properties["label"] = uri.label();

    if (!uri.message().empty())
        properties["message"] = uri.message();

    if (!uri.r().empty())
        properties["r"] = uri.r();

    properties["scheme"] = "bitcoin";

    return object{ { "uri", std::move(properties) } };
}

} // namespace explorer
} // namespace libbitcoin
