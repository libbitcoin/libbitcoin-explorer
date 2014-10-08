/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/primitives/base2.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

base2::base2()
    : value_()
{
}

base2::base2(const std::string& binary)
{
    std::stringstream(binary) >> *this;
}

base2::base2(const bitset& value)
{
    if (value.size() > stealth_address::max_prefix_bits)
    {
        std::string binary;
        boost::to_string(value, binary);
        throw invalid_option_value(binary);
    }

    value_ = value;
}

base2::base2(const base2& other)
    : base2(other.value_)
{
}

base2::operator const bitset&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, base2& argument)
{
    std::string binary;
    input >> binary;

    // TODO: test non-binary characters in input.
    bitset bits(binary);

    // Avoids setting the member value if there is an error.
    argument.value_.swap(bits);
    return input;
}

std::ostream& operator<<(std::ostream& output, const base2& argument)
{
    std::string binary;
    boost::to_string(argument.value_, binary);
    output << binary;
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
