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
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

namespace sx {

void line_out(std::ostream& stream, const char* line, 
    const size_t offset, const char* inset)
{
    // safe string length 
    size_t length = std::string(inset).length();

    // overflow safe assurance that offset is always non-negative
    size_t padding = length > offset ? 0 : offset - length;

    // output the inset-offset-line to the specified stream
    stream << inset << std::string(padding, ' ') << line << std::endl;
}

void line_out(std::ostream& stream, const std::vector<char*>& lines,
    const size_t offset, const char* inset)
{
    // we allow empty multi-line values in source data
    if (lines.size() < 1)
        return;

    // emit the first line as inset-offset-line
    line_out(stream, lines[0], offset, inset);

    // emit the remaining lines as offset-line
    std::for_each(++lines.begin(), lines.end(), 
        [&](const char* line){ line_out(stream, line, offset); });
}

std::string read_stdin()
{
    std::istreambuf_iterator<char> first(std::cin), last;
    std::string result(first, last);
    boost::algorithm::trim(result);
    return result;
}

} // sx