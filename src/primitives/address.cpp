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
#include <bitcoin/explorer/primitives/address.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

address::address()
  : value_()
{
}

address::address(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

address::address(const wallet::payment_address& value)
  : address(value.to_string())
{
}

address::address(const address& other)
  : address(other.value_)
{
}

address::address(uint8_t version, const ec_point& point)
  : address(wallet::payment_address(version, point))
{
}

address::address(uint8_t version, const short_hash& hash)
  : address(wallet::payment_address(version, hash))
{
}

address::address(const wallet::hd_private_key& value)
  : address(value.address())
{
}

address::address(const wallet::hd_public_key& value)
  : address(value.address())
{
}

address::operator bool() const
{
    return value_.version() != wallet::payment_address::invalid_version;
}

address::operator const wallet::payment_address&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, address& argument)
{
    std::string base58;
    input >> base58;

    if (!argument.value_.from_string(base58))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(base58));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const address& argument)
{
    output << argument.value_.to_string();
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
