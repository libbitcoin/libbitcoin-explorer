/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BX_UTILITY_HPP
#define BX_UTILITY_HPP

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/client.hpp>

namespace libbitcoin {
namespace explorer {

/**
 * Centralize istream exceptions.
 */
inline void throw_istream_failure(const std::string& message)
{
    throw po::invalid_option_value(message);
}

/**
 * Centralize ostream exceptions.
 */
inline void throw_ostream_failure(const std::string& message)
{
    throw std::iostream::failure(message);
}

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
 * Read an input stream to the specified type.
 * @param      <Value>  The converted type.
 * @param[out] value    The parsed value.
 * @param[in]  input    The stream to convert.
 * @param[in]  trim     True if value should be trimmed before conversion.
 */
template <typename Value>
void deserialize(Value& value, std::istream& input, bool trim);

/**
 * Get client connection settings for the given command.
 * @param      <Command>  The bx command type.
 * @param[in]  command    The bx command instance.
 * return                 The connetion settings for the command.
 */
template <typename Command>
client::connection_settings get_connection(const Command& command);

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
 * Get a message from the specified input stream.
 * @param[in]  stream The input stream to read.
 * @return            The message read from the input stream.
 */
BCX_API std::string read_stream(std::istream& stream);

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
