/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

namespace sx {

void display_error(const char* message)
{
    std::cerr << message << std::endl;
}

void display_line(const char* message)
{
    std::cout << message << std::endl;
}

std::string read_stdin()
{
    std::istreambuf_iterator<char> first(std::cin), last;
    std::string result(first, last);
    boost::algorithm::trim(result);
    return result;
}

} // sx