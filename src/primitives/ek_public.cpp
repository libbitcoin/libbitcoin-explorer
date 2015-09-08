/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/primitives/ek_public.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace po;
using namespace bc::bip38;

namespace libbitcoin {
namespace explorer {
namespace primitives {

// public_key format is currently private to bx.
bool decode_key(public_key& key, const std::string& encoded)
{
    return decode_base58(key, encoded) && verify_checksum(key);
}

static std::string encode_key(const public_key& key)
{
    return encode_base58(key);
}

ek_public::ek_public()
  : value_()
{
}

ek_public::ek_public(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

ek_public::ek_public(const public_key& value)
  : value_(value)
{
}

ek_public::ek_public(const ek_public& other)
  : ek_public(other.value_)
{
}

public_key& ek_public::data()
{
    return value_;
}

ek_public::operator const public_key&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, ek_public& argument)
{
    std::string hexcode;
    input >> hexcode;

    if (!decode_key(argument.value_, hexcode))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const ek_public& argument)
{
    output << encode_key(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
