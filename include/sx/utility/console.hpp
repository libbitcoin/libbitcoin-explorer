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
#include <tuple>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/lexical_cast.hpp>
#pragma warning(pop)
#include <bitcoin/bitcoin.hpp>

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
enum console_result : int
{
    failure = -1,
    okay = 0,
    invalid = 1
};

/**
 * Avoid the ternary (just for fun). Must precede tempalte usage for gcc build.
 * You should use with expressions as consequent or alternative as they will be
 * executed regardless of the predicate.
 *
 * @param      <Consequent>  The type of the consequent.
 * @param      <Alternate>   The type of the alternative.
 * @param[in]  antecedent    The proposition's antecedent.
 * @param[in]  consequent    The proposition's consequent (if predicate).
 * @param[in]  consequent    The proposition's alternative (if !predicate).
 * @return                   Either the consequent or the alternative.
 */
template <typename Consequent, typename Alternate>
Consequent if_else(bool antecedent, const Consequent consequent,
    const Alternate alternative)
{
    if (antecedent)
        return consequent;
    else 
        return alternative;
}

/**
 * Conveniently test a numeric value to see if specified flags are set.
 * Caller should ensure that TValue is the same type as TElement (sorry,
 * but there are no type constraints in c++).
 *
 * @param      <Value>     The type of the value to test.
 * @param      <Element>   The type of the elements of flags' enum.
 * @param[in]  value       The value to test.
 * @param[in]  flags       The flags to test.
 * @return                 True if all specified flags are set.
 */
template <typename Value, typename Element>
bool are_flags_set(const Value value, const Element flags)
{
    // This simple template precludes the need to explicitly cast the class
    // enum (with elements already of the proper type) and ensures the flag 
    // test isn't inadvertently inverted.
    return (value & static_cast<Value>(flags)) != 0;
}

/**
 * Find the position of an element in an ordered list.
 *
 * @param      <Element>  The type of list member elements.
 * @param[in]  list       The list to search.
 * @param[in]  element    The element to find.
 * @return                The position or -1 if not found.
 */
template <typename Element>
int find_position(const std::vector<Element>& list, const Element& element)
{
    auto it = std::find(list.begin(), list.end(), element);
    return if_else(it == list.end(), -1, distance(list.begin(), it));
}

/**
 * Find the position of a pair in an ordered list.
 *
 * @param      <Pair>  The type of list member elements.
 * @param[in]  list    The list to search.
 * @param[in]  key     The key to the element to find.
 * @return             The position or -1 if not found.
 */
template <typename Pair, typename Key>
int find_pair_position(const std::vector<Pair>& list, const Key& key)
{
    const auto predicate = [&](const Pair& pair)
    {
        return pair.first == key;
    };

    auto it = std::find_if(list.begin(), list.end(), predicate);
    return if_else(it == list.end(), -1, distance(list.begin(), it));
}

/**
 * Safely convert a text string to the specified type, whitespace ignored.
 *
 * @param      <Value>  The converted type.
 * @param[in]  text     The text to convert.
 * @param[out] value    The parsed value.
 * @return              True if successful.
 */
template <typename Value>
bool parse(Value& value, const std::string& text)
{
    std::string serialized(text);
    boost::algorithm::trim(serialized);
    try
    {
        value = boost::lexical_cast<Value>(serialized);
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
 * @param      <Value>   The type to serialize.
 * @param[in]  value     The instance to convert.
 * @param[in]  fallback  The text to populate if value is empty.
 * @return               The serialized value.
 */
template <typename Value>
std::string serialize(const Value& value, const std::string& fallback = "")
{
    std::string serialized;
    boost::to_string(value, serialized);
    return if_else(serialized.empty(), fallback, serialized);
}

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
 * Fill a buffer with randomness using the default random engine.
 *
 * @param[in]  chunk  The buffer to fill with randomness.
 */
void random_fill(bc::data_chunk& chunk);

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
 * DANGER: do not call this if anything iteresting is going on,
 * like databases open or file operations in progress!
 * Terminates the console process with main_failure return code.
 *
 * @param[in]  error  The error code to test and log before terminating.
 */
void terminate_process_on_error(const std::error_code& error);

/**
 * Trim the left side of a string of the specified characters.
 *
 * @param[out] value   The string to split.
 * @param[out] value   The characters to trim, defaults to SX_SPLIT_DELIMITER.
 */
void trim_left(std::string& value, 
    const std::string& chars=SX_SPLIT_DELIMITER);

} // sx

#endif
