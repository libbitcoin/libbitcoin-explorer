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
#include <bitcoin/explorer/config/electrum.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

constexpr auto prefix_standard = "standard";
constexpr auto prefix_witness = "witness";
constexpr auto prefix_two_factor_authentication = "2fa";
constexpr auto prefix_two_factor_authentication_witness = "2faw";


electrum::electrum()
  : value_(type::standard)
{
}

electrum::electrum(const electrum& other)
  : value_(other.value_)
{
}

electrum::electrum(const std::string& token)
{
    std::stringstream(token) >> *this;
}

electrum::electrum(const type& value)
  : value_(value)
{
}

electrum::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, electrum& argument)
{
    std::string text;
    input >> text;

    if (text == prefix_standard)
        argument.value_ = electrum::type::standard;
    else if (text == prefix_witness)
        argument.value_ = electrum::type::witness;
    else if (text == prefix_two_factor_authentication)
        argument.value_ = electrum::type::two_factor_authentication;
    else if (text == prefix_two_factor_authentication_witness)
        argument.value_ = electrum::type::two_factor_authentication_witness;
    else
        throw system::istream_exception(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const electrum& argument)
{
    std::string text;

    switch (argument.value_)
    {
        case electrum::type::standard:
            text = prefix_standard;
            break;
        case electrum::type::witness:
            text = prefix_witness;
            break;
        case electrum::type::two_factor_authentication:
            text = prefix_two_factor_authentication;
            break;
        case electrum::type::two_factor_authentication_witness:
            text = prefix_two_factor_authentication_witness;
            break;
        default:
            throw system::ostream_exception("electrum");
    };

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
