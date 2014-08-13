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
#include <sx/serializer/hd_private.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>

using namespace libwallet;
using namespace po;

namespace sx {
namespace serializer {

hd_private::hd_private()
    : value_()
{
}

hd_private::hd_private(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

hd_private::hd_private(const hd_private_key& value)
{
    // hd_private_key doesn't provide a copy constructor.
    value_.set_encoded(value.encoded());
}

hd_private::hd_private(const hd_private& other)
    : hd_private(other.value_)
{
}

hd_private_key& hd_private::data()
{
    return value_;
}

hd_private::operator const hd_private_key&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, hd_private& argument)
{
    std::string base58;
    input >> base58;

    if (!argument.value_.set_encoded(base58))
        throw invalid_option_value(base58);

    return input;
}

std::ostream& operator<<(std::ostream& output, const hd_private& argument)
{
    output << argument.value_.encoded();
    return output;
}

} // sx
} // serializer