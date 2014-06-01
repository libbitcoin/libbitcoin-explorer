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
#ifndef SX_ENVIRONMENT_HPP
#define SX_ENVIRONMENT_HPP

#include <sx/utility/compat.hpp>

namespace sx {

/**
* Get the value of the SX_CFG environment variable.
*
* @return  The value of the SX_CFG environment variable.
*/
tstring get_sx_cfg();

/**
 * Get the user's home directory.
 *
 * @return  The user's home directory.
 */
tstring home_directory();

/**
 * Set the value of the SX_CFG environment variable to the specified path.
 *
 * @param[in]  path  The path to set into the SX_CFG environment variable.
 * @return           True if successful.
 */
bool set_sx_cfg(const tpath& path);

} // sx

#endif