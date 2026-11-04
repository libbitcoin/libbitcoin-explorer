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
#include <bitcoin/explorer/config/share.hpp>

#include <sstream>
#include <bitcoin/system.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;

share::share()
  : value_{}
{
}

share::share(const std::string& token)
{
    std::stringstream(token) >> *this;
}

share::share(const type& value)
  : value_(value)
{
}

share::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, share& argument)
{
    const std::istreambuf_iterator<char> begin{ input }, end{};
    const std::string sentence{ begin, end };

    argument.value_ = wallet::slip39{ sentence };
    if (!argument.value_)
        throw istream_exception(sentence);

    return input;
}

std::ostream& operator<<(std::ostream& output, const share& argument)
{
    output << argument.value_.sentence();
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
