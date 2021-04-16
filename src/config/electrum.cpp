/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/config/electrum.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;
using namespace po;

// Custom bx option values.
static const auto prefix_old = "version1";
static const auto prefix_standard = "standard";
static const auto prefix_witness = "witness";
static const auto prefix_two_factor_authentication = "2fa";
static const auto prefix_two_factor_authentication_witness = "2faw";

using prefix = wallet::electrum::seed_prefix;

electrum::electrum()
  : value_(prefix::standard)
{
}

electrum::electrum(const std::string& version)
{
    std::stringstream(version) >> *this;
}

electrum::electrum(prefix prefix)
  : value_(prefix)
{
}

electrum::electrum(const electrum& other)
  : value_(other.value_)
{
}

electrum::operator prefix() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, electrum& argument)
{
    std::string version;
    input >> version;

    if (version == prefix_old)
        argument.value_ = prefix::old;
    else if (version == prefix_standard)
        argument.value_ = prefix::standard;
    else if (version == prefix_witness)
        argument.value_ = prefix::witness;
    else if (version == prefix_two_factor_authentication)
        argument.value_ = prefix::two_factor_authentication;
    else if (version == prefix_two_factor_authentication_witness)
        argument.value_ = prefix::two_factor_authentication_witness;
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(version));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const electrum& argument)
{
    std::string version;

    switch (argument.value_)
    {
        case prefix::old:
            version = prefix_old;
            break;
        case prefix::standard:
            version = prefix_standard;
            break;
        case prefix::witness:
            version = prefix_witness;
            break;
        case prefix::two_factor_authentication:
            version = prefix_two_factor_authentication;
            break;
        case prefix::two_factor_authentication_witness:
            version = prefix_two_factor_authentication_witness;
            break;
        default:
            BITCOIN_ASSERT_MSG(false, "Unexpected electrum prefix value.");
    }

    output << version;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin

