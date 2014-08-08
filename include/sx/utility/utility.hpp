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
#ifndef SX_UTILITY_HPP
#define SX_UTILITY_HPP

// Suppressing msvc warnings from boost that are heard to deal with
// because boost/algorithm carelessly defines _SCL_SECURE_NO_WARNINGS
// without sampling it first. 
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
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/lexical_cast.hpp>
#pragma warning(pop)
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/utility/callback_args.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

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
 * Convert a text string to the specified type.
 *
 * @param      <Value>  The converted type.
 * @param[out] value    The parsed value.
 * @param[in]  text     The text to convert.
 */
template <typename Value>
void deserialize(Value& value, const std::string& text)
{
    std::string trimmed(text);
    trim(trimmed);
    value = boost::lexical_cast<Value>(trimmed);
}

/**
 * Read an input stream to the specified type.
 *
 * @param      <Value>  The converted type.
 * @param[out] value    The parsed value.
 * @param[in]  input    The stream to convert.
 */
template <typename Value>
void deserialize(Value& value, std::istream& input)
{
    deserialize(value, read_stream(input));
}

/**
 * Deserialize the tokens of a text string to a vector of the inner type.
 *
 * @param      <Value>     The inner type.
 * @param[out] collection  The parsed vector value.
 * @param[in]  text        The text to convert.
 */
template <typename Value>
void deserialize(std::vector<Value>& collection, const std::string& text)
{
    std::vector<std::string> tokens;
    split(text, tokens, "\n\r\t ");

    for (const auto& token: tokens)
    {
        Value value;
        deserialize(value, token);
        collection.push_back(value);
    }
}

/**
 * Deserialize a satoshi item from the specified binary data.
 *
 * @param      <Item>  The type of the item to parse.
 * @param[out] item    The deserialized item.
 * @param[in]  data    The binary data.
 * @return             True if a item was parsed.
 */
template <typename Item>
bool deserialize_satoshi_item(Item& item, const bc::data_chunk& data)
{
    try
    {
        bc::satoshi_load(data.begin(), data.end(), item);
    }
    catch (bc::end_of_stream)
    {
        return false;
    }
    return true;
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
 * If the variable is not yet loaded, load from stdin as fallback.
 *
 * @param      <Value>    The type of the parameter to load.
 * @param[in]  name       The parameter name.
 * @param[in]  variables  The loaded variables.
 * @param[in]  input      The input stream for loading the parameter.
 */
template <typename Value>
void load_input(Value& parameter, const std::string& name,
    po::variables_map& variables, std::istream& input)
{
    if (variables.find(name) == variables.end())
        deserialize(parameter, input);
}

/**
 * Load file contents as parameter fallback. Obtain the path from the parameter
 * in the variables map.
 *
 * @param      <Value>    The type of the parameter to load.
 * @param[in]  name       The parameter name.
 * @param[in]  variables  The loaded variables.
 */
template <typename Value>
void load_path(Value& parameter, const std::string& name,
     po::variables_map& variables)
{
    // The path is not set as an argument so we can't load from file.
    auto variable = variables.find(name);
    if (variable == variables.end())
        return;

    // Get the argument value as a string.
    const auto path = boost::any_cast<std::string>(variable->second.value());
    
    // The path is the stdio sentinal, so clear parameter and don't read file.
    if (path == SX_STDIO_PATH_SENTINEL)
    {
        variables.erase(variable);
        return;
    }

    // Create a file input stream.
    std::ifstream file(path, std::ifstream::binary);
    if (file.fail())
        throw po::invalid_option_value(path);

    deserialize(parameter, file);
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
std::string serialize(const Value& value, const std::string& fallback="")
{
    std::string text;
    boost::to_string(value, text);
    return if_else(text.empty(), fallback, text);
}

/**
 * Serialize the specified satoshi item to binary data.
 * The data will be resized as necessary to fit the item.
 *
 * @param       <Item>  The type of the item.
 * @param[out] data     The binary data.
 * @param[in]  item     The satoshi item.
 */
template <typename Item>
void serialize_satoshi_item(bc::data_chunk& data, const Item& item)
{
    data.resize(bc::satoshi_raw_size(item));
    bc::satoshi_save(item, data.begin());
}

/**
 * Write a value to a file in the specified path and otherwise to the 
 * specified stream. Not unit testable due to embedded file i/o.
 *
 * @param      Instance   The type of the instance to write.
 * @param[out] output     The fallback out stream.
 * @param[in]  path       The file path or stdio sentinel or empty.
 * @param[in]  terminate  Indicates /n should be added (defaults to true).
 * @param[in]  instance   The instance to serialize.
 */
template <typename Instance>
void write_output(std::ostream& output, const std::string& path,
    const Instance& instance, bool terminate=true)
{        
    if (path.empty() || path == SX_STDIO_PATH_SENTINEL)
    {
        output << instance;
        if (terminate)
            output << std::endl;
    }
    else
    {
        std::ofstream file(path, std::ofstream::binary);
        file << instance;
        if (terminate)
            file << std::endl;
    }
}

/**
 * Handle the callback error with standard behavior.
 *
 * @param[in]  args       The arguments for the callback.
 * @param[in]  error      The callback error result.
 * @param[in]  format     A single parameter format string or empty/default.
 */
void handle_error(callback_args& args, const std::error_code& error,
    std::string format="%1%");

/**
 * Join a list of strings into a single string, in order.
 *
 * @param[in]  words      The list of strings to join.
 * @param[in]  sentence   The resulting string.
 * @param[in]  delimiter  The delimiter, defaults to SX_SENTENCE_DELIMITER.
 */
void join(const std::vector<std::string>& words, std::string& sentence,
    const std::string& delimiter=SX_SENTENCE_DELIMITER);

/**
 * Generate a new ec key from a seed.
 *
 * @param[in]  seed  The seed for key randomness.
 * @return           The new key.
 */
bc::ec_secret new_key(bc::data_chunk& seed);

/**
 * Generate a new pseudorandom seed.
 *
 * @param[in]  seed  The seed length in bits. Will be aligned to nearest byte.
 * @return           The new key.
 */
bc::data_chunk new_seed(size_t bitlength=128);

/**
 * Get the local time, second level resolution, based on the time zone settings
 * of the computer.
 *
 * @return  The local time.
 */
boost::posix_time::ptime now();

/**
 * Fill a buffer with randomness using the default random engine.
 *
 * @param[in]  chunk  The buffer to fill with randomness.
 */
void random_fill(bc::data_chunk& chunk);

/**
 * Get a message from the specified input stream.
 *
 * @param[in]  stream The input stream to read.
 * @return            The message read from the input stream.
 */
std::string read_stream(std::istream& stream);

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
 * @param[in]  delimiter  The delimeter, defaults to SX_SENTENCE_DELIMITER.
 */
void split(const std::string& sentence, std::vector<std::string>& words,
    const std::string& delimiter=SX_SENTENCE_DELIMITER);

/**
 * Trim a string of whitespace.
 *
 * @param[out] value  The string to trim.
 */
void trim(std::string& value);

/**
 * Trim the left side of a string of the specified characters.
 *
 * @param[out] value  The string to split.
 * @param[in] value   The characters to trim, defaults to SX_SENTENCE_DELIMITER.
 */
void trim_left(std::string& value, 
    const std::string& chars=SX_SENTENCE_DELIMITER);

} // sx

#endif
