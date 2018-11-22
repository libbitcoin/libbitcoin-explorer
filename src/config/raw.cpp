/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/config/raw.hpp>

#include <iostream>
#include <sstream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;

raw::raw()
  : value_()
{
}

raw::raw(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

raw::raw(const data_chunk& value)
  : value_(value)
{
}

raw::raw(const raw& other)
  : raw(other.value_)
{
}

raw::operator const data_chunk&() const
{
    return value_;
}

raw::operator data_slice() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, raw& argument)
{
    std::istreambuf_iterator<char> first(input), last;
    argument.value_.assign(first, last);
    return input;
}

std::ostream& operator<<(std::ostream& output, const raw& argument)
{
    std::ostreambuf_iterator<char> iterator(output);
    std::copy(argument.value_.begin(), argument.value_.end(), iterator);
    return output;
}

} // namespace explorer
} // namespace config
} // namespace libbitcoin
