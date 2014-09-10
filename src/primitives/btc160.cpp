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
#include "precompile.hpp"
#include <explorer/primitives/btc160.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/base16.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

btc160::btc160()
    : value_()
{
}

btc160::btc160(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

btc160::btc160(const short_hash& value)
    : value_(value)
{
}

// This drops the address version number.
btc160::btc160(const payment_address& address)
    : btc160(address.hash())
{
}

btc160::btc160(const btc160& other)
    : btc160(other.value_)
{
}

short_hash& btc160::data()
{
    return value_;
}

btc160::operator const short_hash&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, btc160& argument)
{
    std::string hexcode;
    input >> hexcode;

    auto hash = decode_short_hash(hexcode);
    if (hash == null_short_hash)
        throw invalid_option_value(hexcode);

    std::copy(hash.begin(), hash.end(), argument.value_.begin());
    return input;
}

std::ostream& operator<<(std::ostream& output, const btc160& argument)
{
    output << base16(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
