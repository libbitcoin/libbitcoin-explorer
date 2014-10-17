/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#ifndef BX_CONFIG_HPP
#define BX_CONFIG_HPP

#include <cstdint>
#include <string>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {

///**
// * The default configuration file name to use when the path/file has not been
// * otherwise specified.
// */
//#ifdef _WIN32
//    #define BX_DEFAULT_CONFIG_FILE_NAME "explorer_cfg.ini"
//    #define BX_DEFAULT_CLIENT_CERTIFICATE ".explorer.cfg.cer"
//#else
//    #define BX_DEFAULT_CONFIG_FILE_NAME "explorer_cfg"
//    #define BX_DEFAULT_CLIENT_CERTIFICATE ".explorer.cfg"
//#endif

/**
 * Get the default configuration settings file path or return empty.
 * @return  The default configuration settings file path or empty.
 */
BCX_API std::string config_default();

} // namespace explorer
} // namespace libbitcoin

#endif