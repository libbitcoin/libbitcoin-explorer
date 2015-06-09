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
#include <bitcoin/explorer/primitives/point.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/btc256.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

// point format is currently private to bx.
static bool decode_point(chain::output_point& point, const std::string& tuple)
{
    const auto tokens = split(tuple, BX_TX_POINT_DELIMITER);
    if (tokens.size() != 2)
        return false;

    // validate and deserialize the transaction hash
    const btc256 digest(tokens[0]);
    const hash_digest& txhash = digest;

    // copy the input point values
    std::copy(txhash.begin(), txhash.end(), point.hash.begin());
    deserialize(point.index, tokens[1], true);

    return true;
}

// point format is currently private to bx.
static std::string encode_point(const chain::output_point& point)
{
    std::stringstream result;
    result << btc256(point.hash()) << BX_TX_POINT_DELIMITER << point.index();
    return result.str();
}

point::point()
    : value_()
{
}

point::point(const std::string& tuple)
{
    std::stringstream(tuple) >> *this;
}

point::point(const chain::output_point& value)
    : value_(value)
{
}

point::point(const point& other)
    : point(other.value_)
{
}

point::operator const chain::output_point&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, point& argument)
{
    std::string tuple;
    input >> tuple;

    if (!decode_point(argument.value_, tuple))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(tuple));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const point& argument)
{
    output << encode_point(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
