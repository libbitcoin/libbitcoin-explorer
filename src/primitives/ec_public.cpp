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
#include <bitcoin/explorer/primitives/ec_public.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

// ec_point format is currently private to bx.
static bool decode_point(ec_point& point, const std::string& encoded)
{
    data_chunk result;
    if (!decode_base16(result, encoded))
        return false;

    if (!verify_public_key_fast(ec_point(result)))
        return false;

    point.assign(result.begin(), result.end());
    return true;
}

static std::string encode_point(const ec_point& point)
{
    return encode_base16(point);
}

ec_public::ec_public()
    : value_()
{
}

ec_public::ec_public(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

ec_public::ec_public(const bc::ec_point& value)
    : value_(value)
{
}

ec_public::ec_public(const ec_public& other)
    : ec_public(other.value_)
{
}

ec_public::ec_public(const hd_private_key& value)
    : ec_public(value.public_key())
{
}

ec_public::ec_public(const hd_public_key& value)
    : ec_public(value.public_key())
{
}

ec_point& ec_public::data()
{
    return value_;
}

ec_public::operator const ec_point&() const
{
    return value_;
}

ec_public::operator data_slice() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, ec_public& argument)
{
    std::string hexcode;
    input >> hexcode;

    if (!decode_point(argument.value_, hexcode))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const ec_public& argument)
{
    output << encode_point(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
