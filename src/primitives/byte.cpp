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
#include <sx/serializer/byte.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>
#include <boost/program_options.hpp>
#include <sx/define.hpp>
#include <sx/utility/utility.hpp>

using namespace po;

namespace sx {
namespace serializer {

byte::byte()
    : value_()
{
}

byte::byte(const std::string& number)
{
    std::stringstream(number) >> *this;
}

byte::byte(const uint8_t& value)
    : value_(value)
{
}

byte::byte(const byte& other)
    : byte(other.value_)
{
}

uint8_t& byte::data()
{
    return value_;
}

byte::operator const uint8_t&() const
{
    return value_;
}

byte& byte::operator++()
{
    ++value_;
    return *this;
}

byte byte::operator++(int)
{
    byte temp(*this);
    operator++();
    return temp;
}

//byte& byte::operator--()
//{
//    --value_;
//    return *this;
//}
//
//byte byte::operator--(int)
//{
//    byte temp(*this);
//    operator--();
//    return temp;
//}

std::istream& operator>>(std::istream& input, byte& argument)
{
    std::string text;
    input >> text;

    deserialize(argument.value_, text);
    // throw invalid_option_value(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const byte& argument)
{
    output << static_cast<int>(argument.value_);
    return output;
}

} // sx
} // serializer