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
#ifndef SX_MAIN_HPP
#define SX_MAIN_HPP

#include <memory>
#include <string>
#include <sx/command.hpp>

namespace sx {

/**
 * Success return code for int main().
 */
const int main_success = 0;

/**
 * Failure return code for int main().
 */
const int main_failure = -1;

/**
 * Invoke the command identified by the specified arguments.
 * The first argument in the array is the command symbolic name.
 *
 * @param argc the number of elements in the argv parameter.
 * @param argv an array of command line arguments, exlcuding the process.
 * @return True if invoked successfully, otherwise false.
 */
bool dispatch_invoke(const int argc, const char* argv[]);

/**
 * Display usage for all commands.
 *
 * @return True if displayed successfully, otherwise false.
 */
bool dispatch_usage();

/**
 * Display usage for the command identified by the symbolic command name.
 *
 * @param argc the number of elements in the argv parameter.
 * @return True if displayed successfully, otherwise false.
 */
bool dispatch_usage(std::string& symbol);

/**
 * Display usage for the specified command.
 *
 * @param command a pointer to the command to display.
 * @return True if displayed successfully, otherwise false.
 */
bool display_usage(std::shared_ptr<command> command);

/**
 * Invoke the command with the raw arguments as provided on the command line.
 *
 * @param argc the number of elements in the argv array.
 * @param argv the array of arguments, including the process.
 * @return Success (main_success) or failure (main_failure).
 */
int invoke(const int argc, const char* argv[]);

} // sx

#endif