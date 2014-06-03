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

namespace sx {

tstring get_sx_cfg()
{
#ifdef _WIN32
    tchar environment_buffer[MAX_PATH];
    return tstring(GetEnvironmentVariableW(L"SX_CFG", environment_buffer,
        MAX_PATH) != FALSE ? environment_buffer : L"");
#else
    const char* config_path = getenv("SX_CFG");
    return std::string(config_path == nullptr ? "" : config_path);
#endif
}

tstring home_directory()
{
#ifdef _WIN32
    tchar app_data_path[MAX_PATH];
    const auto result = SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL,
        SHGFP_TYPE_CURRENT, app_data_path);
    return tstring(SUCCEEDED(result) ? app_data_path : L"");
#else
    const char* home_path = getenv("HOME");
    return std::string(home_path == nullptr ? getpwuid(getuid())->pw_dir :
        home_path);
#endif
}

bool set_sx_cfg(const tpath& path)
{
#ifdef _WIN32
    return SetEnvironmentVariableW(L"SX_CFG", path.c_str()) != FALSE;
#else
    putenv(("SX_CFG=" + path.generic_string()).c_str());
#endif
}

} // sx