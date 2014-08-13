/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include "precompile.hpp"
#include <sx/serializer/ec_public.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/hex.hpp>

using namespace bc;
using namespace libwallet;
using namespace po;

namespace sx {
namespace serializer {

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

std::istream& operator>>(std::istream& input, ec_public& argument)
{
    std::string hexcode;
    input >> hexcode;

    ec_point point = hex(hexcode);
    if (!verify_public_key_fast(point) /*|| !verify_public_key(point)*/)
        throw invalid_option_value(hexcode);
        
    argument.value_.assign(point.begin(), point.end());
    return input;
}

std::ostream& operator<<(std::ostream& output, const ec_public& argument)
{
    output << hex(argument.value_);
    return output;
}

} // sx
} // serializer