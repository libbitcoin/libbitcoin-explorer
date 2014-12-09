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
#include <bitcoin/explorer/primitives/base10.hpp>

#include <cstdint>
#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

base10::base10()
    : value_(0)
{
}

base10::base10(const std::string& btc)
{
    std::stringstream(btc) >> *this;
}

base10::base10(uint64_t satoshi)
    : value_(satoshi)
{
}

base10::base10(const base10& other)
    : value_(other.value_)
{
}

base10::operator uint64_t() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, base10& argument)
{
    std::string bitcoins;
    input >> bitcoins;

    if (!decode_base10(argument.value_, bitcoins, btc_decimal_places))
        BOOST_THROW_EXCEPTION(invalid_option_value(bitcoins));

    return input;
}

std::ostream& operator<<(std::ostream& output, const base10& argument)
{
    std::string bitcoins;
    bitcoins = encode_base10(argument.value_, btc_decimal_places);
    output << bitcoins;
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
