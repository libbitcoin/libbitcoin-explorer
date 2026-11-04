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
#include <bitcoin/explorer/config/group.hpp>

#include <sstream>
#include <bitcoin/system.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;

constexpr auto separator = "/";

group::group()
  : value_{}
{
}

group::group(const std::string& token)
{
    std::stringstream(token) >> *this;
}

group::group(const type& value)
  : value_(value)
{
}

group::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, group& argument)
{
    std::string text;
    input >> text;

    const auto tokens = split(text, separator, false, false);
    if (tokens.size() != two ||
        !deserialize(argument.value_.threshold, tokens.front()) ||
        !deserialize(argument.value_.count, tokens.back()))
        throw istream_exception(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const group& argument)
{
    output << serialize(argument.value_.threshold) << separator
        << serialize(argument.value_.count);

    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
