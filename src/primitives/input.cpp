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
#include <bitcoin/explorer/primitives/input.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/point.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

static void parse_input(tx_input_type& input,
    const std::vector<std::string>& tokens)
{
    input.script = script_type();
    input.sequence = max_sequence;
    input.previous_output = point(tokens[0] + ":" + tokens[1]);
    if (tokens.size() == 3)
        deserialize(input.sequence, tokens[2]);
}

input::input()
    : value_()
{
}

input::input(const std::string& tuple)
{
    std::stringstream(tuple) >> *this;
}

input::input(const tx_input_type& value)
    : value_(value)
{
}

input::input(const input& other)
    : input(other.value_)
{
}

input::input(const input_point& value)
{
    value_.previous_output = value;
    value_.sequence = max_sequence;
    value_.script = script_type();
}

input::operator const tx_input_type&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& stream, input& argument)
{
    std::string tuple;
    stream >> tuple;

    const auto tokens = split(tuple, BX_TX_POINT_DELIMITER);
    if (tokens.size() != 2 && tokens.size() != 3)
        BOOST_THROW_EXCEPTION(invalid_option_value(tuple));

    parse_input(argument.value_, tokens);
    return stream;
}

std::ostream& operator<<(std::ostream& output, const input& argument)
{
    const auto& out = argument.value_;
    output << point(out.previous_output) << BX_TX_POINT_DELIMITER 
        << out.sequence;
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
