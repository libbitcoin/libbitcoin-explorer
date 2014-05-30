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
#include "command_line.hpp"

/**
 * Invoke the sx library with the raw arguments provided on the command line.
 *
 * @param argc the number of elements in the argv array.
 * @param argv the array of arguments, including the process.
 * @return Success (main_success) or failure (main_failure).
 */
int main(int argc, char* argv[])
{
    return invoke(argc, const_cast<const char**>(argv));
}