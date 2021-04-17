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
#include <bitcoin/explorer/config/sighash.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

constexpr auto sighash_all = "all";
constexpr auto sighash_none = "none";
constexpr auto sighash_single = "single";

sighash::sighash()
  : value_(type::all)
{
}

sighash::sighash(const sighash& other)
  : value_(other.value_)
{
}

sighash::sighash(const std::string& token)
{
    std::stringstream(token) >> *this;
}

sighash::sighash(const type& value)
  : value_(value)
{
}

sighash::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, sighash& argument)
{
    std::string text;
    input >> text;

    if (text == sighash_all)
        argument.value_ = sighash::type::all;
    else if (text == sighash_none)
        argument.value_ = sighash::type::none;
    else if (text == sighash_single)
        argument.value_ = sighash::type::single;
    else
        throw istream_failure(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const sighash& argument)
{
    std::string text;

    switch (argument.value_)
    {
        case sighash::type::all:
            text = sighash_all;
            break;
        case sighash::type::none:
            text = sighash_none;
            break;
        case sighash::type::single:
            text = sighash_single;
            break;
        default:
            throw ostream_failure("sighash");
    }

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
