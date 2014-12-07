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
#include <bitcoin/explorer/utility/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

static void parse_point(output_point& point,
    const std::vector<std::string>& tokens)
{
    // validate and deserialize the transaction hash
    const btc256 digest(tokens[0]);
    const hash_digest& txhash = digest;

    // copy the input point values
    std::copy(txhash.begin(), txhash.end(), point.hash.begin());
    deserialize(point.index, tokens[1]);
}

point::point()
    : value_()
{
}

point::point(const std::string& tuple)
{
    std::stringstream(tuple) >> *this;
}

point::point(const output_point& value)
    : value_(value)
{
}

point::point(const point& other)
    : point(other.value_)
{
}

point::operator const output_point&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, point& argument)
{
    std::string tuple;
    input >> tuple;

    const auto tokens = split(tuple, BX_TX_POINT_DELIMITER);
    if (tokens.size() != 2)
        BOOST_THROW_EXCEPTION(invalid_option_value(tuple));

    parse_point(argument.value_, tokens);
    return input;
}

std::ostream& operator<<(std::ostream& output, const point& argument)
{
    // see concat_point()
    const auto& out = argument.value_;
    output << btc256(out.hash) << BX_TX_POINT_DELIMITER << out.index;
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
