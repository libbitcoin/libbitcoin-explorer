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
#include <bitcoin/explorer/primitives/stealth.hpp>

#include <iostream>
#include <cstdint>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base58.hpp>
#include <bitcoin/explorer/primitives/ec_public.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

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

stealth::stealth(const stealth_address& address)
    : value_(address)
{
}

stealth::stealth(const bc::binary_type& prefix, const ec_public& scan_key,
    const std::vector<ec_public>& spend_keys, uint8_t signatures, bool testnet)
{
    // Normalize signatures between 1 and spend_keys.size().
    const auto size = if_else(spend_keys.empty(), (size_t)1, spend_keys.size());
    auto sigs = if_else(signatures == 0, size, signatures);
    sigs = if_else(sigs > size, size, sigs);

    // Convert the primitives vector to a point vector and apply 'reuse'.
    auto spend_points = cast<ec_public, ec_point>(spend_keys);
    if (spend_points.empty())
        spend_points.push_back(scan_key);

    // Persist the value as an address object.
    value_ = stealth_address(prefix, scan_key, spend_points, sigs, testnet);
}

stealth::stealth(const stealth& other)
    : value_(other.value_)
{
}

stealth::operator bool() const
{
    return value_.valid();
}

stealth::operator const stealth_address&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, stealth& argument)
{
    std::string encoded;
    input >> encoded;

    if (!argument.value_.set_encoded(encoded))
        BOOST_THROW_EXCEPTION(invalid_option_value(encoded));

    return input;
}

std::ostream& operator<<(std::ostream& output, const stealth& argument)
{
    output << argument.value_.encoded();
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
