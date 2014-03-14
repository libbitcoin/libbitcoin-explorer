#include "config.hpp"

#include <sys/types.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <libconfig.h++>

const char* DEFAULT_SERVICE_HOST = "tcp://37.139.11.99:9091";

#ifdef _WINDOWS
#include <shlobj.h>
#include <windows.h>
const wchar_t* home_directory()
{
    wchar_t app_data_path[MAX_PATH];
    auto result = SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL,
        SHGFP_TYPE_CURRENT, app_data_path);
    return SUCCEEDED(result) ? app_data_path : nullptr;
}
const wchar_t* sx_environment_path()
{
    wchar_t environment_buffer[MAX_PATH];
    return GetEnvironmentVariableW(L"SX_CFG", environment_buffer, MAX_PATH) == 
        TRUE ? environment_buffer : nullptr;
}
#else
#include <unistd.h>
#include <pwd.h>
const char* home_directory()
{
    const char* home_path = getenv("HOME");
    return (home_path == nullptr) ? getpwuid(getuid())->pw_dir : home_path;
}
const char* sx_environment_path()
{
    return getenv("SX_CFG");
}
#endif

template <typename T>
void get_value(const libconfig::Setting& root, config_map_type& config_map,
    const std::string& key_name, const T& fallback_value)
{
    T value;
    config_map[key_name] = (root.lookupValue(key_name, value)) ?
        boost::lexical_cast<std::string>(value) :
        boost::lexical_cast<std::string>(fallback_value);
}

void set_config_root(libconfig::Config& configuration, 
    boost::filesystem::path& config_path)
{
    // Ignore error if unable to read config file.
    try
    {
        configuration.readFile(config_path.generic_string().c_str());
    }
    catch (const libconfig::FileIOException&) {}
    catch (const libconfig::ParseException&) {}
}

void load_config(config_map_type& config_map)
{
    // Get configuration file path.
    auto env_path = sx_environment_path();
    auto config_path = (env_path == nullptr) ?
        boost::filesystem::path(home_directory()) / ".sx.cfg" :
        boost::filesystem::path(env_path);

    // Initialize configuration reader.
    libconfig::Config configuration;
    set_config_root(configuration, config_path);

    // Load configuration settings.
    get_value<std::string>(configuration.getRoot(), config_map, "service",
        DEFAULT_SERVICE_HOST);
}