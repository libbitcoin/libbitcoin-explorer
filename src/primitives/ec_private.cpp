/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
// #include "precompile.hpp"
#include <bitcoin/explorer/primitives/ec_private.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/btc256.hpp>
#include <bitcoin/explorer/primitives/wif.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

ec_private::ec_private()
    : value_()
{
}

ec_private::ec_private(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

ec_private::ec_private(const ec_secret& value)
    : value_(value)
{
}

ec_private::ec_private(const hd_private_key& value)
    : ec_private(value.private_key())
{
}

ec_private::ec_private(const ec_private& other)
    : ec_private(other.value_)
{
}

ec_secret& ec_private::data()
{
    return value_;
}

ec_private::operator const ec_secret&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, ec_private& argument)
{
    std::string hexcode;
    input >> hexcode;
        
    ec_secret secret = btc256(hexcode);
    if (!verify_private_key(secret))
        throw invalid_option_value(hexcode);

    std::copy(secret.begin(), secret.end(), argument.value_.begin());
    return input;
}

std::ostream& operator<<(std::ostream& output, const ec_private& argument)
{
    output << btc256(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
