/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
#ifndef BX_UTILITY_HPP
#define BX_UTILITY_HPP

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <system_error>
#include <tuple>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/lexical_cast.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {

/**
 * Types for defining name-value pair list.
 */
typedef std::pair<std::string, std::string> name_value_pair;
typedef std::vector<name_value_pair> name_value_pairs;

/**
 * Forward declaration to break header cycle.
 */
class command;

/**
 * Convert a text string to the specified type.
 * @param      <Value>  The converted type.
 * @param[in]  text     The text to convert.
 * @param[in]  trim     True if value should be trimmed before conversion.
 * return               The parsed value.
 */
template <typename Value>
Value deserialize(const std::string& text, bool trim);

/**
 * Read an input stream to the specified type.
 * @param      <Value>  The converted type.
 * @param[in]  input    The stream to convert.
 * @param[in]  trim     True if value should be trimmed before conversion.
 * return               The parsed value.
 */
template <typename Value>
Value deserialize(std::istream& input, bool trim);

/**
 * Convert a text string to the specified type.
 * @param      <Value>  The converted type.
 * @param[out] value    The parsed value.
 * @param[in]  text     The text to convert.
 * @param[in]  trim     True if value should be trimmed before conversion.
 */
template <typename Value>
void deserialize(Value& value, const std::string& text, bool trim);

/**
 * Read an input stream to the specified type.
 * @param      <Value>  The converted type.
 * @param[out] value    The parsed value.
 * @param[in]  input    The stream to convert.
 * @param[in]  trim     True if value should be trimmed before conversion.
 */
template <typename Value>
void deserialize(Value& value, std::istream& input, bool trim);

/**
 * Deserialize the tokens of a text string to a vector of the inner type.
 * @param      <Value>     The inner type.
 * @param[out] collection  The parsed vector value.
 * @param[in]  text        The text to convert.
 * @param[in]  trim        True if value should be trimmed before conversion.
 */
template <typename Value>
void deserialize(std::vector<Value>& collection, const std::string& text,
    bool trim);

/**
 * Deserialize a satoshi item from the specified binary data.
 * @param      <Item>  The type of the item to parse.
 * @param[out] item    The deserialized item.
 * @param[in]  data    The binary data.
 * @return             True if a item was parsed.
 */
template <typename Item>
bool deserialize_satoshi_item(Item& item, const data_chunk& data);

/**
 * If the variable is not yet loaded, load from stdin as fallback.
 * @param      <Value>    The type of the parameter to load.
 * @param[in]  name       The parameter name.
 * @param[in]  variables  The loaded variables.
 * @param[in]  input      The input stream for loading the parameter.
 * @param[in]  raw        True if the input is raw (should not be trimmed).
 */
template <typename Value>
void load_input(Value& parameter, const std::string& name,
    po::variables_map& variables, std::istream& input, bool raw);

/**
 * Load file contents as parameter fallback. Obtain the path from the parameter
 * in the variables map.
 * @param      <Value>    The type of the parameter to load.
 * @param[in]  name       The parameter name.
 * @param[in]  variables  The loaded variables.
 * @param[in]  raw        True if the file is raw (should not be trimmed).
 */
template <typename Value>
void load_path(Value& parameter, const std::string& name,
    po::variables_map& variables, bool raw);

/**
 * Conveniently convert an instance of the specified type to string.
 * @param      <Value>   The type to serialize.
 * @param[in]  value     The instance to convert.
 * @param[in]  fallback  The text to populate if value is empty.
 * @return               The serialized value.
 */
template <typename Value>
std::string serialize(const Value& value, const std::string& fallback="");

/**
 * Serialize the specified satoshi item to binary data.
 * The data will be resized as necessary to fit the item.
 * @param       <Item>  The type of the item.
 * @param[out] data     The binary data.
 * @param[in]  item     The satoshi item.
 */
template <typename Item>
data_chunk serialize_satoshi_item(const Item& item);

/**
 * Write a value to a file in the specified path and otherwise to the 
 * specified stream. Not unit testable due to embedded file i/o.
 * @param      Instance   The type of the instance to write.
 * @param[out] output     The fallback out stream.
 * @param[in]  path       The file path or stdio sentinel or empty.
 * @param[in]  terminate  Indicates /n should be added (defaults to true).
 * @param[in]  instance   The instance to serialize.
 */
template <typename Instance>
void write_file(std::ostream& output, const std::string& path,
    const Instance& instance, bool terminate=true);

/**
 * Get the connection settings for the configured network.
 * @param    command  The command.
 * @returns           A structure containing the connection settings.
 */
BCX_API client::connection_type get_connection(const command& command);

/**
 * Generate a new ec key from a seed.
 * @param[in]  seed  The seed for key randomness.
 * @return           The new key.
 */
BCX_API ec_secret new_key(const data_chunk& seed);

/**
 * Generate a new pseudorandom seed.
 * @param[in]  seed  The seed length in bits. Will be aligned to nearest byte.
 * @return           The new key.
 */
BCX_API data_chunk new_seed(size_t bit_length=minimum_seed_bits);

/**
 * Convert a list of indexes to a list of strings. This could be generalized.
 * @param[in]  indexes  The list of indexes to convert.
 * @return              The list of strings.
 */
BCX_API string_list numbers_to_strings(const chain::point::indexes& indexes);

/**
 * DEPRECATED in favor of libbitcoin::pseudo_random_fill.
 * Fill a buffer with randomness using the default random engine.
 * @param[in]  chunk  The buffer to fill with randomness.
 */
BCX_API void random_fill(data_chunk& chunk);

/**
 * Get a message from the specified input stream.
 * @param[in]  stream The input stream to read.
 * @return            The message read from the input stream.
 */
BCX_API std::string read_stream(std::istream& stream);

/**
 * Convert any script to an opcode::raw_data script (e.g. for input signing).
 * @param[in]  script  The script to convert.
 * @return             The data script.
 */
BCX_API chain::script script_to_raw_data_script(const chain::script& script);

/**
 * Split a list of tokens with delimiters into a name-value pair list.
 * @param[in]  tokens     The string to test
 * @param[in]  delimiter  The delimiter, defualts to ":".
 * @return                The name-value pair list.
 */
name_value_pairs split_pairs(const std::vector<std::string> tokens,
    const std::string delimiter=":");

/**
 * Determine if a string starts with another (case insensitive).
 * @param[in]  value   The string to test
 * @param[in]  prefix  The prefix to test against.
 * @return             True if the value is prefixed by the prefix.
 */
BCX_API bool starts_with(const std::string& value, const std::string& prefix);

/**
 * Unwrap a wrapped payload.
 * @param[in]  data     The data structure to accept the unwrap.
 * @param[in]  wrapped  The wrapped data to unwrap.
 * @return              True if input checksum validates.
 */
BCX_API bool unwrap(wallet::wrapped_data& data, data_slice wrapped);

/**
 * Wrap arbitrary data.
 * @param[in]  data  The data structure to wrap.
 * @return           The wrapped data.
 */
BCX_API data_chunk wrap(const wallet::wrapped_data& data);

/**
 * Serialize a property tree using a specified encoding.
 * @param[out] output  The output stream to write to.
 * @param[in]  tree    The property tree to serialize.
 * @param[in]  engine  The stream writing engine type to use, defaults to info.
 * @return             The output stream (for convenience).
 */
BCX_API std::ostream& write_stream(std::ostream& output, const pt::ptree& tree,
    encoding_engine engine=encoding_engine::info);

} // namespace explorer
} // namespace libbitcoin

#include <bitcoin/explorer/impl/utility.ipp>

#endif
