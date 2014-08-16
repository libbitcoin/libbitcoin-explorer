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
#include <sx/serializer/wrapper.hpp>

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/prop_tree.hpp>
#include <sx/serializer/base16.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace po;
using namespace pt;

namespace sx {
namespace serializer {

wrapper::wrapper()
    : value_()
{
}

wrapper::wrapper(const std::string& wrapped)
{
    std::stringstream(wrapped) >> *this;
}

wrapper::wrapper(const data_chunk& wrapped)
{
    unwrap(value_, base16(wrapped));
}

wrapper::wrapper(const wrapped_data& wrapped)
    : value_(wrapped)
{
}

wrapper::wrapper(uint32_t version, const data_chunk& payload)
{
    value_.version = version;
    value_.payload = payload;
    value_.checksum = bitcoin_checksum(payload);
}

wrapper::wrapper(const wrapper& other)
    : value_(other.value_)
{
}

wrapper::operator const data_chunk() const
{
    return wrap(value_);
}

wrapper::operator const wrapped_data&() const
{
    return value_;
}

wrapper::operator const ptree() const
{
    return prop_tree(value_);
}

std::istream& operator>>(std::istream& input, wrapper& argument)
{
    std::string hexcode;
    input >> hexcode;

    if (!unwrap(argument.value_, base16(hexcode)))
        throw invalid_option_value(hexcode);

    return input;
}

std::ostream& operator<<(std::ostream& output, const wrapper& argument)
{
    const auto wrapped = wrap(argument.value_);
    output << base16(wrapped);
    return output;
}

} // sx
} // serializer