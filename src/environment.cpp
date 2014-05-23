#ifdef _WIN32
#include <shlobj.h>
#include <tchar.h>
#include <windows.h>
#else
#include <pwd.h>
#include <unistd.h>
#endif
#include "environment.hpp"

tstring home_directory()
{
#ifdef _WIN32
    tchar app_data_path[MAX_PATH];
    auto result = SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL,
        SHGFP_TYPE_CURRENT, app_data_path);
    return tstring(SUCCEEDED(result) ? app_data_path : L"");
#else
    const char* home_path = getenv("HOME");
    return std::string(home_path == nullptr ? getpwuid(getuid())->pw_dir :
        home_path);
#endif
}

tstring sx_config_path()
{
#ifdef _WIN32
    tchar environment_buffer[MAX_PATH];
    return tstring(GetEnvironmentVariableW(L"SX_CFG", environment_buffer,
        MAX_PATH) == TRUE ? environment_buffer : L"");
#else
    const char* config_path = getenv("SX_CFG");
    return std::string(config_path == nullptr ? "" : config_path);
#endif
}