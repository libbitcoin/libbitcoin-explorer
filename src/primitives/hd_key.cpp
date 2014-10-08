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

#include <bitcoin/explorer/primitives/hd_key.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/hd_priv.hpp>
#include <bitcoin/explorer/primitives/hd_pub.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

hd_key::hd_key()
    : private_key_value_(), public_key_value_()
{
}

hd_key::hd_key(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

hd_key::hd_key(const hd_private_key& value)
{
    // hd_public_key doesn't provide a copy constructor.
    private_key_value_.set_encoded(value.encoded());
}

hd_key::hd_key(const hd_public_key& value)
{
    // hd_public_key doesn't provide a copy constructor.
    public_key_value_.set_encoded(value.encoded());
}

hd_key::hd_key(const hd_key& other)
{
    public_key_value_ = other.public_key_value_;
    private_key_value_ = other.private_key_value_;
}

const hd_public_key& hd_key::derived_public_key() const
{
    if (private_key_value_.valid())
        return (hd_public_key&)private_key_value_;
    else
        return public_key_value_;
}

hd_key::operator const hd_private_key&() const
{
    return private_key_value_;
}

hd_key::operator const hd_public_key&() const
{
    return public_key_value_;
}

std::istream& operator>>(std::istream& input, hd_key& argument)
{
    std::string base58;
    input >> base58;

    // First try to read as a private key.
    if (!argument.private_key_value_.set_encoded(base58))
    {
        // Otherwise try to read as a public key.
        if (!argument.public_key_value_.set_encoded(base58))
            throw invalid_option_value(base58);
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const hd_key& argument)
{
    const auto& public_key = argument.derived_public_key();
    output << public_key.encoded();
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
