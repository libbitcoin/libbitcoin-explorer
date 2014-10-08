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

#include <bitcoin/explorer/utility/config.hpp>

#include <string>
#include <boost/filesystem.hpp>
#include <bitcoin/explorer/utility/environment.hpp>

namespace libbitcoin {
namespace explorer {

std::string config_default()
{
    return "";

    // This is disabled so that we can throw an error in the case where a
    // config file is explicitly specified but not otherwise. This ensures
    // that the user can easily confirm that the config file is in use.

    //boost::filesystem::path home(home_directory());
    //if (home.empty())
    //    return "";
    //return (home / BX_DEFAULT_CONFIG_FILE_NAME).generic_string();
}

} // namespace explorer
} // namespace libbitcoin
