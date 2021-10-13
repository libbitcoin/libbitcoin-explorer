/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/config/encoding.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

constexpr auto encoding_info = "info";
constexpr auto encoding_json = "json";
constexpr auto encoding_xml = "xml";

encoding::encoding()
  : encoding(type::info)
{
}

encoding::encoding(const encoding& other)
  : value_(other.value_)
{
}

encoding::encoding(const std::string& token)
{
    std::stringstream(token) >> *this;
}

encoding::encoding(const type& engine)
  : value_(engine)
{
}

encoding::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, encoding& argument)
{
    std::string text;
    input >> text;

    if (text == encoding_info)
        argument.value_ = encoding_engine::info;
    else if (text == encoding_json)
        argument.value_ = encoding_engine::json;
    else if (text == encoding_xml)
        argument.value_ = encoding_engine::xml;
    else
        throw system::istream_exception(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const encoding& argument)
{
    std::string text;

    switch (argument.value_)
    {
        case encoding_engine::info:
            text = encoding_info;
            break;
        case encoding_engine::json:
            text = encoding_json;
            break;
        case encoding_engine::xml:
            text = encoding_xml;
            break;
        default:
            throw system::ostream_exception("encoding");
    }

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
