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
#include <sx/serializer/address.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/ec_public.hpp>

using namespace bc;
using namespace libwallet;
using namespace po;

namespace sx {
namespace serializer {

address::address()
    : value_()
{
}

address::address(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

address::address(const payment_address& value)
    : address(value.encoded())
{
}

address::address(const address& other)
    : address(other.value_)
{
}

address::address(uint8_t version, const short_hash& hash)
    : address(payment_address(version, hash))
{
}

address::address(const hd_private_key& value)
    : address(value.address())
{
}

address::address(const hd_public_key& value)
    : address(value.address())
{
}

payment_address& address::data()
{
    return value_;
}

address::operator const payment_address&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, address& argument)
{
    std::string base58;
    input >> base58;

    if (!argument.value_.set_encoded(base58))
        throw invalid_option_value(base58);

    return input;
}

std::ostream& operator<<(std::ostream& output, const address& argument)
{
    output << argument.value_.encoded();
    return output;
}

} // sx
} // serializer