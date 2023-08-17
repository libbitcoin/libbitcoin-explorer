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
#include <bitcoin/explorer/config/bytes.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

bytes::bytes()
  : value_()
{
}

bytes::bytes(const bytes& other)
  : bytes(other.value_)
{
}

bytes::bytes(const std::string& token)
{
    std::stringstream(token) >> *this;
}

bytes::bytes(const type& value)
  : value_(value)
{
}

bytes::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, bytes& argument)
{
    std::istreambuf_iterator<char> first(input), last;
    argument.value_.assign(first, last);
    return input;
}

std::ostream& operator<<(std::ostream& output, const bytes& argument)
{
    std::ostreambuf_iterator<char> iterator(output);
    std::copy(argument.value_.begin(), argument.value_.end(), iterator);
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
