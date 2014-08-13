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
#include "precompile.hpp"
#include <sx/serializer/header.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/prop_tree.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace po;
using namespace pt;

namespace sx {
namespace serializer {

header::header()
    : value_()
{
}

header::header(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

header::header(const data_chunk& value)
    : header((const std::string&)hex(value))
{
}

header::header(const block_header_type& value)
    : value_(value)
{
}

header::header(const header& other)
    : header(other.value_)
{
}

block_header_type& header::data()
{
    return value_;
}

header::operator const block_header_type&() const
{
    return value_;
}

//header::operator const std::string() const
//{
//    std::stringstream result;
//    result << *this;
//    return result.str();
//}

header::operator const ptree() const
{
    return prop_tree(value_);
}

std::istream& operator>>(std::istream& input, header& argument)
{
    std::string hexcode;
    input >> hexcode;

    if (!deserialize_satoshi_item(argument.value_, hex(hexcode)))
        throw invalid_option_value(hexcode);

    return input;
}

std::ostream& operator<<(std::ostream& output, const header& argument)
{
    const auto bytes = serialize_satoshi_item(argument.value_);
    output << hex(bytes);
    return output;
}

} // sx
} // serializer