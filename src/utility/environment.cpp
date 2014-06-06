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
#ifdef _WIN32
    #include <shlobj.h>
    #include <tchar.h>
    #include <windows.h>
#else
    #include <pwd.h>
    #include <unistd.h>
#endif
#include <sx/utility/environment.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/console.hpp>

namespace sx {
    
tstring get_sx_cfg()
{
#ifdef _WIN32
    tchar path[MAX_PATH];
    auto result = GetEnvironmentVariableW(L"SX_CFG", path, MAX_PATH);
    return if_else(result != FALSE, tstring(path), tstring());
#else
    const char* path = getenv("SX_CFG");
    return if_else(path == nullptr, "", path);
#endif
}

tstring home_directory()
{
#ifdef _WIN32
    tchar path[MAX_PATH];
    const auto result = SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL,
        SHGFP_TYPE_CURRENT, path);
    return if_else(SUCCEEDED(result), tstring(path), tstring());
#else
    const char* path = getenv("HOME");
    return if_else(path == nullptr, getpwuid(getuid())->pw_dir, path);
#endif
}

bool set_sx_cfg(const tpath& path)
{
#ifdef _WIN32
    return SetEnvironmentVariableW(L"SX_CFG", path.c_str()) != FALSE;
#else
    std::string path_variable("SX_CFG=" + path.generic_string());

    // What a crappy API: www.greenend.org.uk/rjk/tech/putenv.html
    // THIS CAST IS AN UGLY HACK FOR A LOUSY API, NEED TO REPLACE.
    // IT COULD CAUSE THE ENV VAR VALUE TO BE RESET, LEAK OR CRASH.
    auto non_const_path_variable = const_cast<char*>(path_variable.c_str());
    putenv(non_const_path_variable);
#endif
}

} // sx