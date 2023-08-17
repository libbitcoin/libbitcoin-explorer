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
#include <bitcoin/explorer/config/witness.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

constexpr auto witness_p2kh_hash = "p2kh";
constexpr auto witness_p2sh_hash = "p2sh";
constexpr auto witness_unknown = "unknown";
constexpr auto witness_invalid = "invalid";

witness::witness()
  : value_(type::invalid)
{
}

witness::witness(const witness& other)
  : value_(other.value_)
{
}

witness::witness(const std::string& token)
{
    std::stringstream(token) >> *this;
}

witness::witness(const type& value)
  : value_(value)
{
}

witness::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, witness& argument)
{
    std::string text;
    input >> text;

    if (text == witness_p2kh_hash)
        argument.value_ = witness::type::version_0_p2kh;
    else if (text == witness_p2sh_hash)
        argument.value_ = witness::type::version_0_p2sh;
    else
        throw system::istream_exception(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const witness& argument)
{
    std::string text;

    if (argument.value_ == witness::type::version_0_p2kh)
        text = witness_p2kh_hash;
    else if (argument.value_ == witness::type::version_0_p2sh)
        text = witness_p2sh_hash;
    else if (argument.value_ == witness::type::unknown)
        text = witness_unknown;
    else if (argument.value_ == witness::type::invalid)
        text = witness_invalid;
    else
        throw system::ostream_exception("witness");

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
