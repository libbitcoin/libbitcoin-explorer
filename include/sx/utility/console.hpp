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
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace sx {

/**
 * Write the specified message, with optional padding and inset text, and a
 * line return, to the specified stream.
 *
 * @param stream the stream to write to.
 * @param line the line to write.
 * @param offset the number of spaces to pad the left side of the line.
 * @param inset text to display in the offset padding.
 */
void line_out(std::ostream& stream, const char* line, 
    const size_t offset = 0, const char* inset = "");

/**
 * Write the specified messages, with optional padding and first line inset 
 * text, and line returns, to the specified stream.
 *
 * @param stream the stream to write to.
 * @param lines the lines to write.
 * @param offset the number of spaces to pad the left side of the line.
 * @param inset text to display in the offset padding.
 */
void line_out(std::ostream& stream, const std::vector<char*>& lines,
    const size_t offset = 0, const char* inset = "");

/**
 * Get a trimmed message from the standard input stream.
 *
 * @return The message read from the standard input stream.
 */
std::string read_stdin();

} // sx

#endif