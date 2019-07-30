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
#include <bitcoin/explorer/config/address_format.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;
using namespace bc::system::wallet;
using namespace po;

static const auto address_format_p2wpkh = "p2wpkh";
static const auto address_format_p2wsh = "p2wsh";

address_format::address_format()
  : value_(witness_address::address_format::p2wpkh)
{
}

address_format::address_format(const std::string& token)
{
    std::stringstream(token) >> *this;
}

address_format::address_format(witness_address::address_format format)
  : value_(format)
{
}

address_format::address_format(const address_format& other)
  : value_(other.value_)
{
}

address_format::operator witness_address::address_format() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, address_format& argument)
{
    std::string text;
    input >> text;

    if (text == address_format_p2wpkh)
    {
        argument.value_ = witness_address::address_format::p2wpkh;
    }
    else if (text == address_format_p2wsh)
    {
        argument.value_ = witness_address::address_format::p2wsh;
    }
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(text));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const address_format& argument)
{
    std::string text;

    if (argument.value_ == witness_address::address_format::p2wpkh)
    {
        text = address_format_p2wpkh;
    }
    else if (argument.value_ == witness_address::address_format::p2wsh)
    {
        text = address_format_p2wsh;
    }
    else
    {
        BITCOIN_ASSERT_MSG(false, "Unexpected address_format value.");
    }

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
