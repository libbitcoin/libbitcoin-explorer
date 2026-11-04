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
#include <bitcoin/explorer/config/electrum.hpp>

#include <sstream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

constexpr auto prefix_old = "old";
constexpr auto prefix_bip39 = "bip39";
constexpr auto prefix_standard = "standard";
constexpr auto prefix_witness = "witness";
constexpr auto prefix_two_factor_authentication = "2fa";
constexpr auto prefix_two_factor_authentication_witness = "2faw";
constexpr auto prefix_none = "none";


electrum::electrum()
  : value_(type::standard)
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

    if (text == prefix_old)
        argument.value_ = electrum::type::old;
    else if (text == prefix_bip39)
        argument.value_ = electrum::type::bip39;
    else if (text == prefix_standard)
        argument.value_ = electrum::type::standard;
    else if (text == prefix_witness)
        argument.value_ = electrum::type::witness;
    else if (text == prefix_two_factor_authentication)
        argument.value_ = electrum::type::two_factor_authentication;
    else if (text == prefix_two_factor_authentication_witness)
        argument.value_ = electrum::type::two_factor_authentication_witness;
    else if (text == prefix_none)
        argument.value_ = electrum::type::none;
    else
        throw istream_exception(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const electrum& argument)
{
    std::string text;

    switch (argument.value_)
    {
        case electrum::type::old:
            text = prefix_old;
            break;
        case electrum::type::bip39:
            text = prefix_bip39;
            break;
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
        case electrum::type::none:
            text = prefix_none;
            break;
        LCOV_EXCL_START("Unreachable with a valid enumeration value.")
        default:
            throw ostream_exception("electrum");
        LCOV_EXCL_STOP()
    };

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
