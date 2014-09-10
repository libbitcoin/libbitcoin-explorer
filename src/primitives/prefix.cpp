/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include "precompile.hpp"
#include <explorer/primitives/prefix.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/utility/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

prefix::prefix()
    : value_()
{
}

prefix::prefix(const std::string& binary)
{
    std::stringstream(binary) >> *this;
}

prefix::prefix(const bitset& value)
{
    if (value.size() > stealth_address::max_prefix_bits)
    {
        std::string binary;
        boost::to_string(value, binary);
        throw invalid_option_value(binary);
    }

    value_ = value;
}

prefix::prefix(const prefix& other)
    : prefix(other.value_)
{
}

prefix::operator const bitset&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, prefix& argument)
{
    std::string binary;
    input >> binary;

    // TODO: test non-binary characters in input.

    bitset bits(binary);
    if (bits.size() > stealth_address::max_prefix_bits)
        throw invalid_option_value(binary);

    // Avoids setting the member value if there is an error.
    argument.value_.swap(bits);
    return input;
}

std::ostream& operator<<(std::ostream& output, const prefix& argument)
{
    std::string binary;
    boost::to_string(argument.value_, binary);
    output << binary;
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
