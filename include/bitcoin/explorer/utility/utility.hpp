/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

#ifdef _MSC_VER
// Suppressing msvc warnings from boost that are heard to deal with
// because boost/algorithm carelessly defines _SCL_SECURE_NO_WARNINGS
// without sampling it first. 
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
#include <cstddef>
#include <iostream>
#include <cstdint>
#include <string>
#include <system_error>
#include <tuple>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/lexical_cast.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {

/**
 * Cast vector/enumerable elements into a new vector.
 * @param      <Source>  The source element type.
 * @param      <Target>  The target element type.
 * @param[in]  source    The enumeration of Source elements to cast.
 * @returns              A new enumeration with elements cast to Target.
 */
template <typename Source, typename Target>
std::vector<Target> cast(const std::vector<Source> source);

/**
 * Avoid the ternary (just for fun). Must precede tempalte usage for gcc build.
 * You should use with expressions as consequent or alternative as they will be
 * executed regardless of the predicate.
 * @param      <Consequent>  The type of the consequent.
 * @param      <Alternate>   The type of the alternative.
 * @param[in]  antecedent    The proposition's antecedent.
 * @param[in]  consequent    The proposition's consequent (if predicate).
 * @param[in]  consequent    The proposition's alternative (if !predicate).
 * @return                   Either the consequent or the alternative.
 */
template <typename Consequent, typename Alternate>
Consequent if_else(bool antecedent, const Consequent consequent,
    const Alternate alternative);

/**
 * Convert a text string to the specified type.
 * @param      <Value>  The converted type.
 * @param[out] value    The parsed value.
 * @param[in]  text     The text to convert.
 */
template <typename Value>
void deserialize(Value& value, const std::string& text);

/**
 * Read an input stream to the specified type.
 * @param      <Value>  The converted type.
 * @param[out] value    The parsed value.
 * @param[in]  input    The stream to convert.
 */
template <typename Value>
void deserialize(Value& value, std::istream& input);

/**
 * Deserialize the tokens of a text string to a vector of the inner type.
 * @param      <Value>     The inner type.
 * @param[out] collection  The parsed vector value.
 * @param[in]  text        The text to convert.
 */
template <typename Value>
void deserialize(std::vector<Value>& collection, const std::string& text);

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
 * Find the position of an element in an ordered list.
 * @param      <Element>  The type of list member elements.
 * @param[in]  list       The list to search.
 * @param[in]  element    The element to find.
 * @return                The position or -1 if not found.
 */
template <typename Element>
int find_position(const std::vector<Element>& list, const Element& element);

/**
 * Find the position of a pair in an ordered list.
 * @param      <Pair>  The type of list member elements.
 * @param[in]  list    The list to search.
 * @param[in]  key     The key to the element to find.
 * @return             The position or -1 if not found.
 */
template <typename Pair, typename Key>
int find_pair_position(const std::vector<Pair>& list, const Key& key);

/**
 * Facilitate a list insertion sort by inserting into a sorted position.
 * @param      <Type>       The type of list member elements.
 * @param      <Predicate>  The sort predicate function signature.
 * @param[in]  list         The list to search.
 * @param[in]  element      The element to insert.
 * @param[in]  predicate    The sort predicate.
 * @return                  Thevector iterator.
 */
template<typename Type, typename Predicate>
typename std::vector<Type>::iterator insert_sorted(std::vector<Type>& list,
    Type const& element, Predicate predicate);
/**
 * If the variable is not yet loaded, load from stdin as fallback.
 * @param      <Value>    The type of the parameter to load.
 * @param[in]  name       The parameter name.
 * @param[in]  variables  The loaded variables.
 * @param[in]  input      The input stream for loading the parameter.
 */
template <typename Value>
void load_input(Value& parameter, const std::string& name,
    po::variables_map& variables, std::istream& input);

/**
 * Load file contents as parameter fallback. Obtain the path from the parameter
 * in the variables map.
 * @param      <Value>    The type of the parameter to load.
 * @param[in]  name       The parameter name.
 * @param[in]  variables  The loaded variables.
 */
template <typename Value>
void load_path(Value& parameter, const std::string& name,
    po::variables_map& variables);

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
 * Join a list of strings into a single string, in order.
 * @param[in]  words      The list of strings to join.
 * @param[in]  sentence   The resulting string.
 * @param[in]  delimiter  The delimiter, defaults to BX_SENTENCE_DELIMITER.
 */
void join(const std::vector<std::string>& words, std::string& sentence,
    const std::string& delimiter=BX_SENTENCE_DELIMITER);

/**
 * Determine if a string is base2.
 * @param[in]  text  The string to test.
 * @return           True if text is base2.
 */
bool is_base2(const std::string& text);

/**
 * Generate a new ec key from a seed.
 * @param[in]  seed  The seed for key randomness.
 * @return           The new key.
 */
ec_secret new_key(const data_chunk& seed);

/**
 * Generate a new pseudorandom seed.
 * @param[in]  seed  The seed length in bits. Will be aligned to nearest byte.
 * @return           The new key.
 */
data_chunk new_seed(size_t bitlength=128);

/**
 * Get the local time, second level resolution, based on the time zone settings
 * of the computer.
 * @return  The local time.
 */
boost::posix_time::ptime now();

/**
 * Fill a buffer with randomness using the default random engine.
 * @param[in]  chunk  The buffer to fill with randomness.
 */
void random_fill(data_chunk& chunk);

/**
 * Get a message from the specified input stream.
 * @param[in]  stream The input stream to read.
 * @return            The message read from the input stream.
 */
std::string read_stream(std::istream& stream);

/*
 * Convert any script to an opcode::raw_data script (e.g. for input signing).
 * @param[in]  script  The script to convert.
 * @return             The data script.
 */
script_type script_to_raw_data_script(const script_type& script);

/*
 * Create a signature for a single transaction input.
 * Sign the single input corresponding output to our index.
 * @param[out] signature    The signature.
 * @param[in]  transaction  The script to convert.
 * @param[in]  index        The input ordinal position within the transaction.
 * @param[in]  script       The previous output (prevout) script.
 * @param[in]  secret       The secret to use for signing.
 * @param[in]  nonce        The nonce (use once) random value for signing.
 * @param[in]  hash_type    Signal which inputs to sign (defaults to single).
 * @return                  True if successful.
 */
bool sign_transaction(data_chunk& signature, const tx_type& transaction,
    size_t index, const script_type& script, const ec_secret& secret,
    const data_chunk& nonce, uint32_t hash_type=sighash::single);

/**
 * Sleep for the specified number of milliseconds.
 * @param[in]  milliseconds  The number of milliseconds to sleep.
 */
void sleep_ms(uint32_t milliseconds);

/**
 * Split a list of strings into a string vector string, in order, white space
 * delimited.
 * @param[in]  sentence   The string to split.
 * @param[in]  delimiter  The delimeter, defaults to BX_SENTENCE_DELIMITER.
 * @return                The list of resulting strings.
 */
std::vector<std::string> split(const std::string& sentence,
    const std::string& delimiter=BX_SENTENCE_DELIMITER);

/**
 * Trim a string of whitespace.
 * @param[out] value  The string to trim.
 */
void trim(std::string& value);

/**
 * Trim the left side of a string of the specified characters.
 * @param[out] value  The string to split.
 * @param[in] value   The characters to trim, defaults to BX_SENTENCE_DELIMITER.
 */
void trim_left(std::string& value, 
    const std::string& chars=BX_SENTENCE_DELIMITER);

/**
 * Unwrap a wrapped payload.
 * @param[in]  data     The data structure to accept the unwrap.
 * @param[in]  wrapped  The wrapped data to unwrap.
 * @return              True if input checksum validates.
 */
bool unwrap(wrapped_data& data, const data_chunk& wrapped);

/**
 * Validate a transaction input signature.
 * @param[in]  tx         The transaction to validate against.
 * @param[in]  index      The ordinal position of the input in the tx.
 * @param[in]  pubkey     The public key to validate against.
 * @param[in]  script     The code script.
 * @param[in]  signature  Thesignature to validate.
 * @param[in]  hash_type  The type of signature hash for which to validate.
 * @return                True if the signature is valid for the context.
 */
bool valid_signature(const tx_type& tx, uint32_t index,
    const ec_point& pubkey, const script_type& script,
    const data_chunk& signature, uint32_t hash_type=sighash::single);

/**
 * Unwrap a wrapped payload.
 * @param[out] version   The version byte of the wrapped data.
 * @param[out] payload   The payload of the wrapped data.
 * @param[out] checksum  The validated checksum of the wrapped data.
 * @param[in]  wrapped   The wrapped data to unwrap.
 * @return               True if input checksum validates.
 */
bool unwrap(uint8_t& version, data_chunk& payload, uint32_t& checksum,
    const data_chunk& wrapped);

/**
 * Wrap arbitrary data.
 * @param[in]  data  The data structure to wrap.
 * @return           The wrapped data.
 */
data_chunk wrap(const wrapped_data& data);

/**
 * Wrap arbitrary data.
 * @param[in]  version  The version byte for the wrapped data.
 * @param[out] payload  The payload to wrap.
 * @return              The wrapped data.
 */
data_chunk wrap(uint8_t version, const data_chunk& payload);

/**
 * Serialize a property tree using a specified encoding.
 * Encoding 'native' is serialized as 'info'.
 * @param[out] output  The output stream to write to.
 * @param[in]  tree    The property tree to serialize.
 * @param[in]  engine  The stream writing engine type to use, defaults to info.
 * @return             The output stream (for convenience).
 */
std::ostream& write_stream(std::ostream& output, const pt::ptree& tree,
    encoding_engine engine=encoding_engine::info);

} // namespace explorer
} // namespace libbitcoin

#include <bitcoin/explorer/impl/utility.ipp>

#endif