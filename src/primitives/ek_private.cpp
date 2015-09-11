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
#include <bitcoin/explorer/primitives/ek_private.hpp>

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

// private_key format is currently private to bx.
static bool decode_key(private_key& key, const std::string& encoded)
{
    return decode_base58(key, encoded) && verify_checksum(key);
}

static std::string encode_key(const private_key& key)
{
    return encode_base58(key);
}

ek_private::ek_private()
  : value_()
{
}

ek_private::ek_private(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

ek_private::ek_private(const private_key& value)
  : value_(value)
{
}

ek_private::ek_private(const ek_private& other)
  : ek_private(other.value_)
{
}

private_key& ek_private::data()
{
    return value_;
}

ek_private::operator const private_key&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, ek_private& argument)
{
    std::string hexcode;
    input >> hexcode;

    if (!decode_key(argument.value_, hexcode))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const ek_private& argument)
{
    output << encode_key(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
