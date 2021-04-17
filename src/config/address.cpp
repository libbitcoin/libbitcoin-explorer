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
#include <bitcoin/explorer/config/address.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

address::address()
  : value_()
{
}

address::address(const address& other)
  : value_(other.value_)
{
}

address::address(const std::string& token)
{
    std::stringstream(token) >> *this;
}

address::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, address& argument)
{
    std::string text;
    input >> text;

    system::wallet::payment_address payment(text);
    if (payment)
    {
        argument.value_ = text;
        return input;
    }

    // Deprecated.
    system::wallet::stealth_address stealth(text);
    if (stealth)
    {
        argument.value_ = text;
        return input;
    }

    // TODO: add witness address.

    throw istream_failure(text);
    return input;
}

std::ostream& operator<<(std::ostream& output, const address& argument)
{
    output << argument.value_;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
