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
#include <bitcoin/explorer/primitives/stealth.hpp>

#include <iostream>
#include <cstdint>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base58.hpp>
#include <bitcoin/explorer/primitives/ec_public.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

stealth::stealth()
    : value_()
{
}

stealth::stealth(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

stealth::stealth(const wallet::stealth_address& address)
    : value_(address)
{
}

stealth::stealth(const bc::binary_type& prefix, const ec_point& scan_key,
    const wallet::pubkey_list& spend_keys, uint8_t signatures, bool testnet)
    : value_(prefix, scan_key, spend_keys, signatures, testnet)
{
}

stealth::stealth(const stealth& other)
    : value_(other.value_)
{
}

stealth::operator bool() const
{
    return value_.valid();
}

stealth::operator const wallet::stealth_address&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, stealth& argument)
{
    std::string encoded;
    input >> encoded;

    if (!argument.value_.from_string(encoded))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(encoded));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const stealth& argument)
{
    output << argument.value_.to_string();
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
