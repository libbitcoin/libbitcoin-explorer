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
#include <bitcoin/explorer/primitives/base85.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

base85::base85()
    : value_()
{
}

base85::base85(const std::string& base85)
{
    std::stringstream(base85) >> *this;
}

// Z85 is unusual in that it requires four byte alignment.
base85::base85(const data_chunk& value)
    : value_(value)
{
    std::string encoded;
    if (!encode_base85(encoded, value))
    {
        BOOST_THROW_EXCEPTION(
            invalid_option_value(encode_base16(value)));
    }
}

base85::base85(const base85& other)
    : base85(other.value_)
{
}

base85::operator const data_chunk&() const
{
    return value_;
}

base85::operator data_slice() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, base85& argument)
{
    std::string base85;
    input >> base85;

    if (!decode_base85(argument.value_, base85))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(base85));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const base85& argument)
{
    std::string decoded;

    // Z85 is unusual in that it requires four byte alignment.
    // We have already guarded construction against this, so we can ignore here.
    /* bool */ encode_base85(decoded, argument.value_);

    output << decoded;
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
