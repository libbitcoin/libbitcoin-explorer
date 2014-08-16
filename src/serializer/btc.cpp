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
#include <sx/serializer/btc.hpp>

#include <cstdint>
#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>

using namespace bc;
using namespace po;

namespace sx {
namespace serializer {

btc::btc()
{
}

btc::btc(const std::string& btc)
{
    std::stringstream(btc) >> *this;
}

btc::btc(uint64_t satoshi)
    : value_(satoshi)
{
}

btc::btc(const btc& other)
    : value_(other.value_)
{
}

btc::operator const uint64_t() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, btc& argument)
{
    std::string bitcoins;
    input >> bitcoins;

    if (!btc_to_satoshi(argument.value_, bitcoins))
        throw invalid_option_value(bitcoins);

    return input;
}

std::ostream& operator<<(std::ostream& output, const btc& argument)
{
    std::string bitcoins;
    bitcoins = satoshi_to_btc(argument.value_);
    output << bitcoins;
    return output;
}

} // sx
} // serializer