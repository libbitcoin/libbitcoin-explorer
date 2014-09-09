/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#ifndef BX_ENVIRONMENT_HPP
#define BX_ENVIRONMENT_HPP

#include <string>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace explorer {

/**
 * Naming convention prefix for Bitcoin Explorer environment variables.
 */
#define BX_ENVIRONMENT_VARIABLE_PREFIX "BX_"

/**
 * The name of the linux environment variable that defines the home directory.
 */
#define BX_LINUX_HOME_ENVIRONMENT_VARIABLE "HOME"

/**
 * Get the user's home directory.
 *
 * @return  The user's home directory.
 */
    std::string home_directory();

} // explorer

#endif