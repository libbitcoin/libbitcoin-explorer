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
#include <bitcoin/explorer/config/btc.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

btc::btc()
  : value_(0)
{
}

btc::btc(const btc& other)
  : value_(other.value_)
{
}

btc::btc(const std::string& token)
{
    std::stringstream(token) >> *this;
}

btc::btc(const type& value)
  : value_(value)
{
}

btc::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, btc& argument)
{
    std::string text;
    input >> text;

    uint64_t out;

    // bitcoins to satoshis (shift 8 decimal places)
    if (!system::decode_base10(out, text, system::btc_decimal_places))
        throw_istream_failure(text);

    argument.value_ = out;
    return input;
}

std::ostream& operator<<(std::ostream& output, const btc& argument)
{
    std::string text;

    // satoshis to bitcoins (shift 8 decimal places)
    text = system::encode_base10(argument.value_, system::btc_decimal_places);

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
