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
#ifndef SX_DISPLAY_HPP
#define SX_DISPLAY_HPP

#include <sx/command.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

/**
 * Display an error message to the console that the specified sx command does
 * not exist.
 * @param[in]  command  The value that was attempted as a command.
 */
void display_invalid_command(const std::string& command);

/**
 * Display an error message to the console that the specified configuration
 * file does not exist.
 * @param[in]  file  The path of a file that was tested.
 */
void display_invalid_config(const std::string& file);

/**
 * Display an error message to the console that indicates what is wrong with
 * initialization in terms of command line, config settings file, environment.
 * @param[in]  message  The message to display.
 */
void display_invalid_variables(const std::string& message);

/**
 * Display a blank line.
 */
void display_line();

/**
 * Display a summary for the specified command.
 * @param[in]  command  Pointer to the command to display.
 * @return              True if displayed successfully.
 */
bool display_summary(const std::shared_ptr<command> command);

/**
 * Display usage instructions (help) for the sx command line.
 */
void display_usage();

/**
 * Display usage for the specified command.
 * @param[in]  command  Pointer to the command to display.
 * @return              True if displayed successfully.
 */
bool display_usage(const std::shared_ptr<command> command);

} // sx

#endif