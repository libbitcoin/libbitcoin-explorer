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
#include <bitcoin/explorer/config/ec_private.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

ec_private::ec_private()
  : value_()
{
}

ec_private::ec_private(const ec_private& other)
  : ec_private(other.value_)
{
}

ec_private::ec_private(const std::string& token)
{
    std::stringstream(token) >> *this;
}

ec_private::ec_private(const type& value)
  : value_(value)
{
}

ec_private::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, ec_private& argument)
{
    std::string text;
    input >> text;

    ec_private::type out;
    if (!system::decode_base16(out, text))
        throw istream_exception(text);

    argument.value_ = out;
    return input;
}

std::ostream& operator<<(std::ostream& output, const ec_private& argument)
{
    output << system::encode_base16(argument.value_);
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
