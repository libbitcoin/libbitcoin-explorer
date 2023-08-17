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

    // Can't rely on cin for uint8_t.
    if (!system::deserialize(argument.value_, text))
        throw system::istream_exception(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const byte& argument)
{
    // Can't rely on cout for uint8_t.
    output << system::serialize(argument.value_);
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
