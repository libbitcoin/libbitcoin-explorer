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

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {

using namespace bc::system;
using namespace bc::system::json;

value checked_to_json(const data_chunk& checked) NOEXCEPT
{
    BC_ASSERT(checked.size() > checksum_default_size);

    const auto payload = std::next(checked.begin());
    const auto tail = std::prev(checked.end(), checksum_default_size);
    data_array<checksum_default_size> checksum{};
    std::copy(tail, checked.end(), checksum.begin());

    return object
    {
        { "wrapper", object
            {
                { "checksum", from_little<uint32_t>(checksum) },
                { "payload", encode_base16(data_chunk{ payload, tail }) },
                { "version", checked.front() }
            }
        }
    };
}

// A property is found in the object or, failing that, within its only member.
static const value* find_property(const value& json,
    const std::string& name) NOEXCEPT
{
    auto object = json.if_object();
    while (!is_null(object))
    {
        if (const auto property = object->if_contains(name))
            return property;

        if (object->size() != one)
            return nullptr;

        object = object->begin()->value().if_object();
    }

    return nullptr;
}

static bool read_property(value& out, std::ostream& error,
    const std::string& json, const std::string& name)
{
    code ec{};
    const auto document = parse(json, ec);
    if (ec)
    {
        error << BX_JSON_INVALID << std::endl;
        return false;
    }

    const auto property = find_property(document, name);
    if (is_null(property))
    {
        error << BX_JSON_MISSING << std::endl;
        return false;
    }

    out = *property;
    return true;
}

static console_result write_value(std::ostream& output, const value& property)
{
    if (const auto text = property.if_string())
        output << *text << std::endl;
    else
        output << serialize(property) << std::endl;

    return console_result::okay;
}

console_result write_property(std::ostream& output, std::ostream& error,
    const std::string& json, const std::string& name)
{
    value property{};
    if (!read_property(property, error, json, name))
        return console_result::failure;

    return write_value(output, property);
}

console_result write_element(std::ostream& output, std::ostream& error,
    const std::string& json, const std::string& name, uint32_t index)
{
    value property{};
    if (!read_property(property, error, json, name))
        return console_result::failure;

    const auto list = property.if_array();
    if (is_null(list))
    {
        error << BX_JSON_NOT_LIST << std::endl;
        return console_result::failure;
    }

    const auto element = list->if_contains(possible_wide_cast<size_t>(index));
    if (is_null(element))
    {
        error << BX_JSON_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    return write_value(output, *element);
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
