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
#ifndef SX_CONSOLE_HPP
#define SX_CONSOLE_HPP

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace sx {

/**
 * Write the specified message, with optional padding and inset text, and a
 * line return, to the specified stream.
 *
 * @param[out] stream  The stream to write to.
 * @param[in]  line    The line to write.
 * @param[in]  offset  Number of spaces to pad the left side of the line.
 * @param[in]  inset   Text to display in the offset padding.
 */
void line_out(std::ostream& stream, const char* line, 
    const size_t offset = 0, const char* inset = "");

/**
* Write the specified message, with optional padding and inset text, and a
* line return, to the specified stream.
*
* @param[out] stream  The stream to write to.
* @param[in]  line    The line to write.
* @param[in]  offset  Number of spaces to pad the left side of the line.
* @param[in]  inset   Text to display in the offset padding.
*/
void line_out(std::ostream& stream, std::string& line,
    const size_t offset = 0, const char* inset = "");

/**
 * Write the specified messages, with optional padding and first line inset 
 * text, and line returns, to the specified stream.
 *
 * @param[in]  stream  The stream to write to.
 * @param[in]  lines   The lines to write.
 * @param[in]  offset  Number of spaces to pad the left side of the line.
 * @param[in]  inset   Text to display in the offset padding.
 */
void line_out(std::ostream& stream, const std::vector<char*>& lines,
    const size_t offset = 0, const char* inset = "");

/**
 * Get a trimmed message from the standard input stream.
 *
 * @return  The message read from the standard input stream.
 */
std::string read_stdin();

/**
* Sleep for the specified number of milliseconds.
*
* @param[in]  milliseconds  The number of milliseconds to sleep.
*/
void sleep_ms(uint32_t milliseconds);

/**
 * Validate that the actual argument count matches the target, and if not emit
 * the specified error message to the standard error stream. The first argument
 * is assumed to be the command symbol.
 *
 * @param[in]  actual   The actual argument count.
 * @param[in]  message  The message to write to the standard error stream.
 * @param[in]  minimum  The minimum target argument count.
 * @param[in]  maximum  The maximum target argument count, zero for unlimited.
 * @return              True if the argument range satisfies the predicate.
 */
bool validate_argument_range(const int actual,
    const std::vector<char*>& message, const int minimum,
    const int maximum = 0);

} // sx

#endif