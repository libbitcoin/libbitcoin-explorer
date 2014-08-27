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
#ifndef SX_ENVIRONMENT_HPP
#define SX_ENVIRONMENT_HPP

#include <string>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace explorer {

/**
 * Naming convention prefix for SX environment variables.
 */
#define SX_ENVIRONMENT_VARIABLE_PREFIX "SX_"

/**
 * The name of the linux environment variable that defines the home directory.
 */
#define SX_LINUX_HOME_ENVIRONMENT_VARIABLE "HOME"

/**
 * Get the user's home directory.
 *
 * @return  The user's home directory.
 */
    std::string home_directory();

} // explorer

#endif