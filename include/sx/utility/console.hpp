/**
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

// Suppressing msvc warnings from boost that are heard to deal with
// because boost/algorithm carelessly defines _SCL_SECURE_NO_WARNINGS
// without testing it first. 
#pragma warning(push)
#pragma warning(disable : 4996)
#include <iostream>
#include <stdint.h>
#include <string>
#include <system_error>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/lexical_cast.hpp>
#pragma warning(pop)

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

/**
 * Default delimiter for use in word joining operations.
 */
#define SX_JOIN_DELIMITER " \n\t"

/**
 * Default delimiter for use in sentence splitting operations.
 */
#define SX_SPLIT_DELIMITER "-"
    
/**
 * Conventional command line argument sentinel for indicating that a file
 * should be read from STDIN.
 */
#define SX_STDIN_PATH_SENTINEL "-"

/**
 * Result codes for int main().
 */
enum class console_result : int
{
    failure = -1,
    okay = 0,
    invalid = 1
};

/**
 * Default ports for the Bitcoin protocol.
 */
enum class port_default : uint16_t
{
    mainnet = 8333,
    testnet = 18333
};

/**
 * Conveniently test a numeric value to see if specified flags are set.
 * Caller should ensure that TValue is the same type as TElement (sorry,
 * but there are no type constraints in c++).
 *
 * @param      <TValue>    The type of the value to test.
 * @param      <TElement>  The type of the elements of flags' class enum.
 * @param[in]  value       The value to test.
 * @param[in]  flags       The flags to test.
 * @return                 True if all specified flags are set.
 */
template <typename TValue, typename TElement>
bool are_flags_set(const TValue value, const TElement flags)
{
    // This simple template precludes the need to explicitly cast the class
    // enum (with elements already of the proper type) and ensures the flag 
    // test isn't inadvertently inverted.
    return (value & static_cast<TValue>(flags)) != 0;
}

/**
 * Safely convert a text string to the specified type, whitespace ignored.
 *
 * @param      <TValue> The converted type.
 * @param[in]  text     The text to convert.
 * @param[out] value    The parsed value.
 * @return              True if successful.
 */
template <typename TValue>
bool parse(TValue& value, const std::string& text)
{
    std::string serialized(text);
    boost::algorithm::trim(serialized);
    try
    {
        value = boost::lexical_cast<TValue>(serialized);
    }
    catch (const boost::bad_lexical_cast&)
    {
        return false;
    }
    return true;
}

/**
 * Conveniently convert an instance of the specified type to string.
 *
 * @param      <TValue>  The type to serialize.
 * @param[in]  value     The instance to convert.
 * @param[in]  fallback  The text to populate if value is empty.
 * @return               The serialized value.
 */
template <typename TValue>
std::string serialize(const TValue& value, const std::string& fallback="")
{
    std::string serialized;
    boost::to_string(value, serialized);
    return serialized.empty() ? fallback : serialized;
}

/**
 * Get the argument from the specified args, in the specified index,
 * or the value specified as the default if the number of args is 
 * insufficient. Fallback defaults to empty string.
 *
 * @param[in]  argc      The number of args.
 * @param[in]  argv      The array of args from which to obtain the argument.
 * @param[in]  stream    The input stream from which to read the argument.
 * @param[in]  fallback  The arg index from which the filename is to be read.
 * @return               The argument, or the fallback if insufficient args.
 */
std::string get_arg(int argc, const char* argv[],
    const std::string& fallback="", int index=1);

/**
 * Get the set of arguments from the specified argv, excluding options.
 *
 * @param[in]  argc       The number of args.
 * @param[in]  argv       The array of args from which to obtain the argument.
 * @param[out] arguments  The read argument values.
 * @return                The number of arguments read and returned in the list.
 */
size_t get_args(int argc, const char* argv[],
    std::vector<std::string>& arguments);

/**
 * Get the argument from the specified args, in the specified index,
 * or the value from the specified stream if the number of args is 
 * insufficient.
 *
 * @param[in]  argc    The number of args.
 * @param[in]  argv    The array of args from which to obtain the argument.
 * @param[in]  stream  The input stream from which to read the argument.
 * @param[in]  index   The arg index from which the filename is to be read.
 * @param[in]  trim    Trim the stream input of whitespace, defaults to false.
 * @return             The argument, or the stream value if insufficient args.
 */
std::string get_arg_or_stream(int argc, const char* argv[],
    std::istream& stream, int index=1, bool trim=false);

/**
 * Get the filename from the specified args, in the specified position,
 * or the default value if the number of args is insufficient.
 *
 * @param[in]  argc    The number of args.
 * @param[in]  argv    The array of args from which to obtain the filename.
 * @return             The filename or the default value if insufficient args.
 */
std::string get_filename(int argc, const char* argv[]);

/**
 * Uniformly test argv for the presence of the specified option, in long
 * or short format. The option can be a single character or a word. If the
 * option is longer than one character then its first character as well as its 
 * entire value will be tested. No other partial tests are made. The option
 * must be lower case and should not contain any leading dash "-" characters.
 *
 * @param[in]  argc      The number of arguments in the arguments vector.
 * @param[in]  argv      The arguments vector.
 * @param[in]  option    The option value to test (must be lower case).
 * @return               True if the option is set.
 */
bool get_option(int argc, const char* argv[], const std::string& option);

/**
 * Uniformly convert a text string to a bool, with whitespace and text case
 * ignored, although beware that case depends upon locale. The following set 
 * defines false boolean text values: { 'false', '0', 'no' } with all other
 * values retuning false.
 *
 * @param[in]  text  The text to text.
 * @return           True if the text value is a member of the false set.
 */
bool is_false(const std::string& text);

/**
 * Uniformly test an argument for the presence of the specified option, in long
 * or short format. The option can be a single character or a word. If the
 * option is longer than one character then its first character as well as its 
 * entire value will be tested. No other partial tests are made. The option
 * must be lower case and should not contain any leading dash "-" characters.
 *
 * @param[in]  argument  The argument to test.
 * @param[in]  option    The option value to test (must be lower case).
 * @return               True if the option is set.
 */
bool is_option(const std::string& argument, const std::string& option);

/**
 * Uniformly test an argument to to determine if it follows the option pattern.
 * Options may be two chars starting with one dash ("-") or more than two chars
 * starting with a double dash ("--").
 *
 * @param[in]  argument  The argument to test.
 * @return               True if the argument is an option.
 */
bool is_option_any(const std::string& argument);

/**
 * Uniformly convert a text string to a bool, with whitespace and text case
 * ignored, although beware that case depends upon locale. The following set
 * defines true boolean text values: { 'true', '1', 'yes' } with all other
 * values retuning false.
 *
 * @param[in]  text  The text to convert.
 * @return           True if the text value is a member of the true set.
 */
bool is_true(const std::string& text);

/**
 * Join a list of strings into a single string, in order.
 *
 * @param[in]  words      The list of strings to join.
 * @param[in]  sentence   The resulting string.
 * @param[in]  delimiter  The delimiter, defaults to SX_JOIN_DELIMITER.
 */
void join(const std::vector<std::string>& words, std::string& sentence,
    const std::string& delimiter=SX_JOIN_DELIMITER);

/**
 * Write the specified message, with optional padding and inset text, and a
 * line return, to the specified stream.
 *
 * @param[out] stream  The stream to write to.
 * @param[in]  line    The line to write.
 * @param[in]  offset  Number of spaces to pad the left side of the line.
 * @param[in]  inset   Text to display in the offset padding.
 */
void line_out(std::ostream& stream, const std::string& line, size_t offset=0,
    const std::string& inset="");

/**
 * Write the specified messages, with optional padding and first line inset 
 * text, and line returns, to the specified stream.
 *
 * @param[in]  stream  The stream to write to.
 * @param[in]  lines   The lines to write.
 * @param[in]  offset  Number of spaces to pad the left side of the line.
 * @param[in]  inset   Text to display in the offset padding.
 */
void line_out(std::ostream& stream, const std::vector<const char*>& lines,
    const size_t offset=0, const std::string& inset="");

/**
 * Get a trimmed message from the specified input stream.
 *
 * @param[in]  stream The input stream to read.
 * @param[in]  trim   Trim the input of whitespace, defaults to false.
 * @return            The message read from the input stream.
 */
std::string read_stream(std::istream& stream, bool trim=false);

/**
 * Sleep for the specified number of milliseconds.
 *
 * @param[in]  milliseconds  The number of milliseconds to sleep.
 */
void sleep_ms(uint32_t milliseconds);

/**
 * Split a list of strings into a string vector string, in order, white space
 * delimited.
 *
 * @param[in]  sentence   The string to split.
 * @param[out] words      The list of resulting strings.
 * @param[in]  delimiter  The delimeter, defaults to SX_SPLIT_DELIMITER.
 */
void split(const std::string& sentence, std::vector<std::string>& words,
    const std::string& delimiter=SX_SPLIT_DELIMITER);

/**
 * Read the specified stream to a string list in order.
 *
 * @param[in]  sentence   The string to split.
 * @param[out] words      The list of resulting strings.
 * @param[in]  delimiter  The delimeter, defaults to SX_SPLIT_DELIMITER.
 */
void stream_to_words(std::istream& stream,
    std::vector<std::string>& words,
    const std::string& delimiter=SX_SPLIT_DELIMITER);

/**
 * DANGER: do not call this if anything iteresting is going on,
 * like databases open or file operations in progress!
 * Terminates the console process with main_failure return code.
 *
 * @param[in]  error  The error code to test and log before terminating.
 */
void terminate_process_on_error(const std::error_code& error);

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
bool validate_argument_range(int actual, 
    const std::vector<const char*>& message, int minimum, int maximum=0);

} // sx

#endif
