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

#include <exception>
#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace po;

// DRY
static auto encoding_info = "info";
static auto encoding_json = "json";
static auto encoding_xml = "xml";
static auto encoding_data = "data";

encoding::encoding()
  : encoding(encoding_engine::info)
{
}

encoding::encoding(const std::string& token)
{
    std::stringstream(token) >> *this;
}

encoding::encoding(encoding_engine engine)
  : value_(engine)
{
}

encoding::encoding(const encoding& other)
  : value_(other.value_)
{
}

encoding::operator encoding_engine() const
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
    else if (text == encoding_data)
        argument.value_ = encoding_engine::data;
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(text));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const encoding& argument)
{
    std::string value;

    switch (argument.value_)
    {
        case encoding_engine::info:
            value = encoding_info;
            break;
        case encoding_engine::json:
            value = encoding_json;
            break;
        case encoding_engine::xml:
            value = encoding_xml;
            break;
        case encoding_engine::data:
            value = encoding_data;
            break;
        default:
            BITCOIN_ASSERT_MSG(false, "Unexpected encoding value.");
    }

    return output;
}

} // namespace explorer
} // namespace config
} // namespace libbitcoin
