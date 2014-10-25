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

#include <bitcoin/explorer/primitives/btc256.hpp>

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

btc256::btc256()
    : value_()
{
}

btc256::btc256(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

btc256::btc256(const hash_digest& value)
    : value_(value)
{
}

btc256::btc256(const btc256& other)
    : btc256(other.value_)
{
}

hash_digest& btc256::data()
{
    return value_;
}

btc256::operator const hash_digest&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, btc256& argument)
{
    std::string hexcode;
    input >> hexcode;

    auto hash = decode_hash(hexcode);
    if (hash == null_hash)
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));

    std::copy(hash.begin(), hash.end(), argument.value_.begin());
    return input;
}

std::ostream& operator<<(std::ostream& output, const btc256& argument)
{
    output << base16(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
