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

namespace sx {
    
#define STDIN_PATH_SENTINEL "-"

/**
 * Success return code for int main().
 */
const int main_success = 0;

/**
 * Failure return code for int main().
 */
const int main_failure = -1;

/**
 * Default mainnet port for Bitcoin protocol.
 */
const uint16_t mainnet_port_default = 8333;

/**
 * Default testnet port for Bitcoin protocol.
 */
const uint16_t testnet_port_default = 18333;
    
/**
 * Get the filename from the specified arguments, in the specified position,
 * or the default value if the number of arguments is insufficient.
 *
 * @param[in]  argc    The number of args.
 * @param[in]  argv    The array of args from which to obtain the filename.
 * @param[in]  index   The arg index from which the filename is to be read.
 * @return             The filename or the default value if insufficient args.
 */
const char* get_filename(const int argc, const char* argv[], 
    const int index = 1);

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
 * Get a trimmed message from STDIN.
 *
 * @param[in]  trim  Trim the input of whitespace, defaults to false.
 * @return           The message read from STDIN.
 */
std::string read_stdin(bool trim = false);

/**
 * Sleep for the specified number of milliseconds.
 *
 * @param[in]  milliseconds  The number of milliseconds to sleep.
 */
void sleep_ms(const uint32_t milliseconds);

/**
 * Uniformly convert a text string to a bool, with whitespace and text case
 * ignored, although beware that case depends upon locale. The following set 
 * defines false boolean text values: { 'false', '0' } with all other values
 * retuning false.
 *
 * @param[in]  text  The text to text.
 * @return           True if the text value is a member of the false set.
 */
bool is_false(const std::string text);

/**
 * Uniformly convert a text string to a bool, with whitespace and text case
 * ignored, although beware that case depends upon locale. The following set
 * defines true boolean text values: { 'true', '1' } with all other values
 * retuning false.
 *
 * @param[in]  text  The text to convert.
 * @return           True if the text value is a member of the true set.
 */
bool is_true(const std::string text);

/**
 * DANGER: do not call this if anything iteresting is going on,
 * like databases open or file operations in progress!
 * Terminates the console process with main_failure return code.
 *
 * @param[in]  text  An error code to log before exiting the process.
 */
void terminate_process(const std::error_code& ec);

/**
 * Uniformly convert a text string to a numeric port identifier.
 *
 * @param[in]  text  The text to convert.
 * @param[out] port  The parsed value.
 * @return           True if successful.
 */
bool to_port(const std::string text, uint16_t& port);

/**
 * Safely convert a text string to a number, with whitespace ignored.
 *
 * @param[in]  text    The text to convert.
 * @param[out] number  The parsed value.
 * @return             True if successful.
 */
bool to_number(const std::string text, size_t& number);

/**
 * Validate that the actual argument count matches the target, and if not emit
 * the specified error message to the STDERR. The first argument
 * is assumed to be the command symbol.
 *
 * @param[in]  actual   The actual argument count.
 * @param[in]  message  The message to write to STDERR.
 * @param[in]  minimum  The minimum target argument count.
 * @param[in]  maximum  The maximum target argument count, zero for unlimited.
 * @return              True if the argument range satisfies the predicate.
 */
bool validate_argument_range(const int actual,
    const std::vector<char*>& message, const int minimum,
    const int maximum = 0);

} // sx

#endif