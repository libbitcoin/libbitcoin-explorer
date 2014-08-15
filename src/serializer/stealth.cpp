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
#include <sx/serializer/stealth.hpp>

#include <iostream>
#include <cstdint>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/prop_tree.hpp>
#include <sx/serializer/base58.hpp>
#include <sx/serializer/ec_public.hpp>

using namespace bc;
using namespace libwallet;
using namespace po;
using namespace pt;

namespace sx {
namespace serializer {

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

stealth::stealth(const stealth_prefix& prefix, const ec_public& scan_key,
    const std::vector<ec_public>& spend_keys, uint8_t signatures,
    bool reuse_key, bool testnet)
{
    // Cast the serializer vector to a point vector and apply reuse.
    const auto size = spend_keys.size() + if_else(reuse_key, 1, 0);
    std::vector<ec_point> spend_points(size);
    spend_points.assign(spend_keys.begin(), spend_keys.end());
    spend_points.push_back(scan_key);

    // Persist the vlaue as an address object.
    value_ = stealth_address(prefix, scan_key, spend_points, signatures,
        testnet);
}

stealth::stealth(const stealth& other)
    : value_(other.value_)
{
}

stealth::operator const stealth_address&() const
{
    return value_;
}

stealth::operator const ptree() const
{
    return prop_tree(value_);
}

std::istream& operator>>(std::istream& input, stealth& argument)
{
    std::string encoded;
    input >> encoded;

    if (!argument.value_.set_encoded(encoded))
        throw invalid_option_value(encoded);

    return input;
}

std::ostream& operator<<(std::ostream& output, const stealth& argument)
{
    output << argument.value_.encoded();
    return output;
}

} // sx
} // serializer