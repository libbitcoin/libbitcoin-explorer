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
#include <bitcoin/explorer/config/algorithm.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

constexpr auto algorithm_greedy = "greedy";
constexpr auto algorithm_individual = "individual";

algorithm::algorithm()
  : value_(type::greedy)
{
}

algorithm::algorithm(const algorithm& other)
  : value_(other.value_)
{
}

algorithm::algorithm(const std::string& token)
{
    std::stringstream(token) >> *this;
}

algorithm::algorithm(const type& value)
  : value_(value)
{
}
algorithm::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, algorithm& argument)
{
    std::string text;
    input >> text;

    if (text == algorithm_greedy)
        argument.value_ = algorithm::type::greedy;
    else if (text == algorithm_individual)
        argument.value_ = algorithm::type::individual;
    else
        throw istream_failure(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const algorithm& argument)
{
    std::string text;

    switch (argument.value_)
    {
        case algorithm::type::greedy:
            text = algorithm_greedy;
            break;
        case algorithm::type::individual:
            text = algorithm_individual;
            break;
        default:
            throw ostream_failure("algorithm");
    };

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
