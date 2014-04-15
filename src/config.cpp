#include "config.hpp"

#include <sys/types.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <libconfig.h++>

#ifdef _WIN32

#include <shlobj.h>
#include <windows.h>
#include <tchar.h>

// Use explicitly wide char functions and compile for unicode.

tstring home_directory()
{
    tchar app_data_path[MAX_PATH];
    auto result = SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL,
        SHGFP_TYPE_CURRENT, app_data_path);
    return tstring(SUCCEEDED(result) ? app_data_path : L"");
}

tstring sx_config_path()
{
    tchar environment_buffer[MAX_PATH];
    return tstring(GetEnvironmentVariableW(L"SX_CFG", environment_buffer,
        MAX_PATH) == TRUE ? environment_buffer : L"");
}

#else

#include <unistd.h>
#include <pwd.h>

// This is ANSI/MBCS if compiled on Windows but is always Unicode on Linux,
// so we can safely return it as tstring when excluded from Windows.

/*
tstring home_directory()
{
    const char* home_path = getenv("HOME");
    return std::string(home_path == nullptr ? getpwuid(getuid())->pw_dir : 
        home_path);
}

tstring sx_config_path()
{
    return std::string(getenv("SX_CFG"));
}
*/

using boost::filesystem::path;

path home_directory()
{
    const char* home_path = getenv("HOME");
    if (!home_path)
    {
        passwd* pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        return path(homedir);
    }
    return path(home_path);
}

#endif

template <typename T>
void get_value(const libconfig::Setting& root, config_map_type& config_map,
    const std::string& key_name, const T& fallback_value)
{
    T value;

    // libconfig is ANSI/MBCS on Windows - no Unicode support.
    // This reads ANSI/MBCS values from XML. If they are UTF-8 (and above the
    // ASCII band) the values will be misinterpreted upon use.
    config_map[key_name] = (root.lookupValue(key_name, value)) ?
        boost::lexical_cast<std::string>(value) :
        boost::lexical_cast<std::string>(fallback_value);
}

void set_config_path(libconfig::Config& configuration, const char* config_path)
{
    // Ignore error if unable to read config file.
    try
    {
        // libconfig is ANSI/MBCS on Windows - no Unicode support.
        // This translates the path from Unicode to a "generic" path in
        // ANSI/MBCS, which can result in failures.
        configuration.readFile(config_path);
    }
    catch (const libconfig::FileIOException&) {}
    catch (const libconfig::ParseException&) {}
}

void load_config(config_map_type& config)
{
    libconfig::Config configuration;
#ifdef _WIN32
    tstring environment_path = sx_config_path();
    tpath config_path = environment_path.empty() ?
        tpath(home_directory()) / L".sx.cfg" : tpath(environment_path);
    set_config_path(configuration, config_path.generic_string().c_str());
#else
    path conf_path = home_directory() / ".sx.cfg";
    // Check for env variable config to override default path.
    char* env_path = getenv("SX_CFG");
    if (env_path)
        conf_path = env_path;
    set_config_path(configuration, conf_path.native().c_str());
#endif

    // Read off values.
    const libconfig::Setting& root = configuration.getRoot();
    get_value<std::string>(root, config, "service", "tcp://37.139.11.99:9091");
    get_value<std::string>(root, config, "client-certificate", ".sx.cert");
    get_value<std::string>(root, config, "server-public-key", "");
}
