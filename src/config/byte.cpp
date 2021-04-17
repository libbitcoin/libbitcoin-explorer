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
#include <bitcoin/explorer/config/byte.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

byte::byte()
  : value_(0)
{
}

byte::byte(const byte& other)
  : byte(other.value_)
{
}

byte::byte(const std::string& token)
{
    std::stringstream(token) >> *this;
}

byte::byte(const type& value)
  : value_(value)
{
}

byte::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, byte& argument)
{
    std::string text;
    input >> text;

    // We have this byte class only because deserialization doesn't
    // treat 8 bit values as decimal numbers (unlike 16+ bit numbers).

    uint16_t number;
    system::deserialize(number, text, true);

    if (number > max_uint8)
        throw istream_failure(text);

    argument.value_ = static_cast<uint8_t>(number);
    return input;
}

std::ostream& operator<<(std::ostream& output, const byte& argument)
{
    uint16_t number(argument.value_);
    output << number;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
