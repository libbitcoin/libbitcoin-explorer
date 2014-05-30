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
#ifndef SX_CONSOLE_HPP
#define SX_CONSOLE_HPP

#include <iostream>
#include <boost/algorithm/string.hpp>

/**
 * Display the specified message followed by a line return to the standard
 * error stream.
 *
 * @param message the message to display.
 */
void display_error(const char* message);

/**
 * Display the specified message followed by a line return to the standard
 * output stream.
 *
 * @param message the message to display.
 */
void display_line(const char* message);

/**
 * Get a trimmed message from the standard input stream.
 *
 * @return The message read from the standard input stream.
 */
std::string read_stdin();

#endif

