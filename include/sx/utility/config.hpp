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
#ifndef SX_CONFIG_HPP
#define SX_CONFIG_HPP

#include <stdint.h>
#include <string>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

/**
 * The default configuration file name to use when the path/file has not been
 * otherwise specified.
 */
#ifdef _WIN32
    #define SX_DEFAULT_CONFIG_FILE_NAME "sx_cfg.ini"
    #define SX_DEFAULT_CLIENT_CERTIFICATE ".sx.cfg.cer"
#else
    #define SX_DEFAULT_CONFIG_FILE_NAME "sx_cfg"
    #define SX_DEFAULT_CLIENT_CERTIFICATE ".sx.cfg"
#endif

/**
 * Get the default configuration settings file path or return empty.
 *
 * @return  The default configuration settings file path or empty.
 */
std::string config_default();

} // sx

#endif