/**
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include "precompile.hpp"
#include <explorer/primitives/encoding.hpp>

#include <exception>
#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>

using namespace po;

namespace explorer {
namespace primitives {

// DRY
static const char* encoding_info = "info";
static const char* encoding_json = "json";
static const char* encoding_xml = "xml";
static const char* encoding_native = "native";

encoding::encoding()
    : encoding(encoding_engine::native)
{
}

encoding::encoding(const std::string& token)
{
    std::stringstream(token) >> *this;
}

encoding::encoding(const encoding_engine& value)
    : value_(value)
{
}

encoding::encoding(const encoding& other)
    : value_(other.value_)
{
}

encoding::operator const encoding_engine() const
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
    else if (text == encoding_native)
        argument.value_ = encoding_engine::native;
    else
        throw invalid_option_value(text);

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
        case encoding_engine::native:
            value = encoding_native;
            break;
        default:
            throw std::exception("Unexpected encoding value.");
    }

    return output;
}

} // explorer
} // primitives
