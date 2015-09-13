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
#include <bitcoin/explorer/primitives/ek_token.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace po;
using namespace bc::wallet;

namespace libbitcoin {
namespace explorer {
namespace primitives {

// wallet::token format is currently private to bx.
static bool decode_token(wallet::token& token, const std::string& encoded)
{
    return decode_base58(token, encoded) && verify_checksum(token);
}

static std::string encode_token(const wallet::token& token)
{
    return encode_base58(token);
}

ek_token::ek_token()
  : value_()
{
}

ek_token::ek_token(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

ek_token::ek_token(const bc::wallet::token& value)
  : value_(value)
{
}

ek_token::ek_token(const ek_token& other)
  : ek_token(other.value_)
{
}

wallet::token& ek_token::data()
{
    return value_;
}

ek_token::operator const wallet::token&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, ek_token& argument)
{
    std::string hexcode;
    input >> hexcode;

    if (!decode_token(argument.value_, hexcode))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const ek_token& argument)
{
    output << encode_token(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
