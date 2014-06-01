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

/* NOTE: don't declare 'using namespace foo' in heders. */

namespace sx {

/**
 * Invoke the command identified by the specified arguments.
 * The first argument in the array is the command symbolic name.
 *
 * @param[in]  argc   The number of elements in the argv parameter.
 * @param[in]  argv   Array of command line arguments excluding the process.
 * @param[in]  alias  An command name to redirect the call to.
 * @return            True if invoked successfully.
 */
bool dispatch_invoke(const int argc, const char* argv[], 
    const char* alias=nullptr);

/**
 * Display a summary for the command identified by the symbolic command name.
 *
 * @param[in]  symbol  The symbolic command name for the command of interest.
 * @return              True if displayed successfully.
 */
bool dispatch_summary(std::string& symbol);

/**
 * Display usage for all commands.
 *
 * @return  True if displayed successfully.
 */
bool dispatch_usage();

/**
 * Display a summary for the specified command.
 *
 * @param[in]  command  Pointer to the command to display.
 * @return              True if displayed successfully.
 */
bool display_summary(std::shared_ptr<command> command);

/**
 * Display usage for the specified command.
 *
 * @param[in]  command  Pointer to the command to display.
 * @return              True if displayed successfully.
 */
bool display_usage(std::shared_ptr<command> command);

/**
 * Invoke the command with the raw arguments as provided on the command line.
 *
 * @param[in]  argc  The number of elements in the argv array.
 * @param[in]  argv  The array of arguments, including the process.
 * @return           Success (sx::main_success) or failure (sx::main_failure).
 */
int invoke(const int argc, const char* argv[]);

} // sx

#endif