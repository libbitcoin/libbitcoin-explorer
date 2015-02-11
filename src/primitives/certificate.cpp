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
#include <bitcoin/explorer/primitives/certificate.hpp>

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

constexpr uint8_t certificate_byte_size = 32;
constexpr uint8_t certificate_string_length = 40;

certificate::certificate()
    : value_()
{
}

certificate::certificate(const std::string& base85)
{
    std::stringstream(base85) >> *this;
}

certificate::certificate(const certificate& other)
    : value_(other.value_)
{
}

// Returns empty string if not initialized.
std::string certificate::get_base85() const
{
    std::stringstream base85;
    base85 << *this;
    return base85.str();
}

certificate::operator const data_chunk&() const
{
    return value_;
}

certificate::operator data_slice() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, certificate& argument)
{
    std::string base85;
    input >> base85;

    if (base85.size() != certificate_string_length || 
        !decode_base85(argument.value_, base85))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(base85));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const certificate& argument)
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
