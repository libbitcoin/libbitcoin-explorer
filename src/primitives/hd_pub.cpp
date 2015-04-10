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
#include <bitcoin/explorer/primitives/hd_pub.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

hd_pub::hd_pub()
    : value_()
{
}

hd_pub::hd_pub(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

hd_pub::hd_pub(const wallet::hd_public_key& value)
{
    // hd_public_key doesn't provide a copy constructor.
    value_.set_encoded(value.encoded());
}

hd_pub::hd_pub(const hd_pub& other)
    : hd_pub(other.value_)
{
}

hd_pub::operator const wallet::hd_public_key&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, hd_pub& argument)
{
    std::string base58;
    input >> base58;

    if (!argument.value_.set_encoded(base58))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(base58));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const hd_pub& argument)
{
    output << argument.value_.encoded();
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
