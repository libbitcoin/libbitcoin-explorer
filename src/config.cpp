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

#include <bitcoin/explorer/config.hpp>

#include <boost/filesystem.hpp>

// Define after boost asio, see stackoverflow.com/a/9750437/1172329.
#ifdef _MSC_VER
    #include <shlobj.h>
    #include <windows.h>
#else
    #include <pwd.h>
    #include <unistd.h>
#endif

namespace libbitcoin {
namespace explorer {

using boost::filesystem::path;

static std::string system_config_directory()
{
#ifdef _MSC_VER
    char directory[MAX_PATH];
    const auto result = SHGetFolderPathA(NULL, CSIDL_COMMON_APPDATA, NULL,
        SHGFP_TYPE_CURRENT, directory);
    if (SUCCEEDED(result))
        return directory;
    return "";
#else
    // This symbol must be defined at compile for this project.
    // Therefore do not move this definition into libbitcoin.
    return std::string(SYSCONFDIR);
#endif
}

path default_config_path()
{
    // This subdirectory and file name must stay in sync with the path
    // for the sample distributed via the build.
    return path(system_config_directory()) / "libbitcoin" / "bx.cfg";
}

} // namespace explorer
} // namespace libbitcoin
