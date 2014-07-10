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
#include <sx/utility/environment.hpp>

#ifdef _WIN32
    #include <shlobj.h>
    #include <windows.h>
#else
    #include <pwd.h>
    #include <unistd.h>
#endif
#include <string>

namespace sx {

std::string home_directory()
{
#ifdef _WIN32
    char path[MAX_PATH];
    const auto result = SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL,
        SHGFP_TYPE_CURRENT, path);
    if (SUCCEEDED(result))
        return path;
    return "";
#else
    const char* path = getenv(SX_LINUX_HOME_ENVIRONMENT_VARIABLE);
    if (path == nullptr)
        return getpwuid(getuid())->pw_dir;
    return path;
#endif
}

} // sx