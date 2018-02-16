/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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

#include <iostream>
#include <string>
#include <cstdint>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin/utility/string.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace po;

byte::byte()
  : value_(0)
{
}

byte::byte(const std::string& decimal)
{
    std::stringstream(decimal) >> *this;
}

byte::byte(uint8_t byte)
  : value_(byte)
{
}

byte::byte(const byte& other)
  : byte(other.value_)
{
}

byte::operator uint8_t() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, byte& argument)
{
    std::string decimal;
    input >> decimal;

    // We have this byte class only because deserialization doesn't
    // treat 8 bit values as decimal numbers (unlike 16+ bit numbers).

    uint16_t number;
    bc::deserialize(number, decimal, true);

    if (number > max_uint8)
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(decimal));
    }

    argument.value_ = static_cast<uint8_t>(number);
    return input;
}

std::ostream& operator<<(std::ostream& output, const byte& argument)
{
    uint16_t number(argument.value_);
    output << number;
    return output;
}

} // namespace explorer
} // namespace config
} // namespace libbitcoin
