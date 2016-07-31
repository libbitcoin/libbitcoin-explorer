/**
 * Copyright (c) 2011-2016 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/config/algorithm.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace config {

static auto algorithm_greedy = "greedy";
static auto algorithm_individual = "individual";

algorithm::algorithm()
  : value_(bc::wallet::select_outputs::algorithm::greedy)
{
}

algorithm::algorithm(const std::string& token)
{
    std::stringstream(token) >> *this;
}

algorithm::algorithm(bc::wallet::select_outputs::algorithm& algorithm)
  : value_(algorithm)
{
}

algorithm::algorithm(const algorithm& other)
  : value_(other.value_)
{
}

algorithm::operator const bc::wallet::select_outputs::algorithm() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, algorithm& argument)
{
    std::string text;
    input >> text;

    if (text == algorithm_greedy)
    {
        argument.value_ = bc::wallet::select_outputs::algorithm::greedy;
    }
    else if (text == algorithm_individual)
    {
        argument.value_ = bc::wallet::select_outputs::algorithm::individual;
    }
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(text));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const algorithm& argument)
{
    std::string text;

    if (argument.value_ == bc::wallet::select_outputs::algorithm::greedy)
    {
        text = algorithm_greedy;
    }
    else if (argument.value_ == bc::wallet::select_outputs::algorithm::individual)
    {
        text = algorithm_individual;
    }
    else
    {
        BITCOIN_ASSERT_MSG(false, "Unexpected algorithm value.");
    }

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
