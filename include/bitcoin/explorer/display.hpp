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
#ifndef BX_DISPLAY_HPP
#define BX_DISPLAY_HPP

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/command.hpp>

namespace libbitcoin {
namespace explorer {

/**
 * Write the list of all command names to a stream.
 * @param[in]  stream  The stream to write into.
 */
BCX_API void display_command_names(std::ostream& stream);

/**
 * Write an error message indicating that the client-server connection failed.
 * @param[in]  stream  The stream to write into.
 * @param[in]  url     The server url.
 */
BCX_API void display_connection_failure(std::ostream& stream, 
    const bc::config::endpoint& url);

/**
 * Write an error message to a stream that the specified explorer command
 * name has been deprecated in favor of another, or does not exist.
 * @param[in]  stream       The stream to write into.
 * @param[in]  command      The value that was attempted as a command.
 * @param[in]  superseding  The superseding command, defaults to empty.
 */
BCX_API void display_invalid_command(std::ostream& stream, 
    const std::string& command, const std::string& superseding="");

/**
 * Write an error message to a stream that indicates what is wrong with
 * initialization in terms of command line, config settings file, environment.
 * @param[in]  stream   The stream to write into.
 * @param[in]  message  The message to write.
 */
BCX_API void display_invalid_parameter(std::ostream& stream,
    const std::string& message);

/**
 * Write usage instructions (help) to a tream for the explorer command line.
 * @param[in]  stream   The stream to write into.
 */
BCX_API void display_usage(std::ostream& stream);

} // namespace explorer
} // namespace libbitcoin

#endif
