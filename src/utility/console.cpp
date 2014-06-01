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
#include <vector>
#pragma warning(push)
//#pragma warning(disable : ????)
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>
#pragma warning(pop)

namespace sx {

const char* get_filename(const int argc, const char* argv[], const int index)
{
    return argc > index ? argv[index] : STDIN_PATH_SENTINEL;
}

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

void line_out(std::ostream& stream, std::string& line,
    const size_t offset, const char* inset)
{
    return line_out(stream, line.c_str(), offset, inset);
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

std::string read_stdin(bool trim)
{
    std::istreambuf_iterator<char> first(std::cin), last;
    std::string result(first, last);
    if (trim)
        boost::algorithm::trim(result);
    return result;
}

void sleep_ms(const uint32_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool is_false(const std::string text)
{
    // a reference is avoided in order to prevent original string corruption
    std::string value(text);

    // case conversion is dependent upon the thread locale
    boost::algorithm::to_lower(value);

    // the concept of string false is hardwired here
    return text == "false" || text == "0";
}

bool is_true(const std::string text)
{
    // a reference is avoided in order to prevent original string corruption
    std::string value(text);

    // case conversion is dependent upon the thread locale
    boost::algorithm::to_lower(value);

    // the concept of string true is hardwired here
    return text == "true" || text == "1";
}

void terminate_process(const std::error_code& ec)
{
    if (!ec)
        return;
    bc::log_fatal() << ec.message();
    exit(main_failure);
}

bool to_number(const std::string text, size_t& number)
{
    // a reference is avoided in order to prevent original string corruption
    std::string value(text);
    boost::algorithm::trim(value);
    try
    {
        number = boost::lexical_cast<size_t>(text);
    }
    catch (const boost::bad_lexical_cast&)
    {
        return false;
    }
    return true;
}

bool to_port(const std::string text, uint16_t& port)
{
    // a reference is avoided in order to prevent original string corruption
    std::string value(text);
    boost::algorithm::trim(value);
    try
    {
        port = boost::lexical_cast<uint16_t>(text);
    }
    catch (const boost::bad_lexical_cast&)
    {
        return false;
    }
    return true;
}

bool validate_argument_range(const int actual,
    const std::vector<char*>& message, const int minimum, 
    const int maximum)
{
    bool valid = ((actual >= minimum) && (maximum == 0 || actual <= maximum));
    if (!valid)
        line_out(std::cerr, message);
    return valid;
}

} // sx