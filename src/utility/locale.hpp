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
#ifndef SX_LOCALE_HPP
#define SX_LOCALE_HPP

#include <string>

/**
 * Display an error message to the console that the specified configuration
 * file does not exist.
 *
 * @param command the value that was attempted as a command.
 */
void display_invalid_command(std::string& command);

/**
 * Display an error message to the console that the specified sx command does
 * not exist.
 *
 * @param the path of a file that was tested.
 */
void display_invalid_config(std::string& file);

/**
 * Display usage instructions (help) for the sx command line.
 */
void display_usage();

#endif