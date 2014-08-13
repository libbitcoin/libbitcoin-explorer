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
#include <sx/serializer/hd_public.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hex.hpp>

using namespace libwallet;
using namespace po;

namespace sx {
namespace serializer {

hd_public::hd_public()
    : value_()
{
}

hd_public::hd_public(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

hd_public::hd_public(const hd_public_key& value)
{
    // hd_public_key doesn't provide a copy constructor.
    value_.set_encoded(value.encoded());
}

hd_public::hd_public(const hd_public& other)
    : hd_public(other.value_)
{
}

hd_public_key& hd_public::data()
{
    return value_;
}

hd_public::operator const hd_public_key&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, hd_public& argument)
{
    std::string base58;
    input >> base58;

    if (!argument.value_.set_encoded(base58))
        throw invalid_option_value(base58);

    return input;
}

std::ostream& operator<<(std::ostream& output, const hd_public& argument)
{
    output << argument.value_.encoded();
    return output;
}

} // sx
} // serializer