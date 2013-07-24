#include "config.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <libconfig.h++>

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

template <typename T>
void get_value(const libconfig::Setting& root, config_map_type& config,
    const std::string& key_name, const T& fallback_value)
{
    T value;
    if (root.lookupValue(key_name, value))
        config[key_name] = boost::lexical_cast<std::string>(value);
    else
        config[key_name] = boost::lexical_cast<std::string>(fallback_value);
}

void load_config(config_map_type& config)
{
    path conf_path = home_directory() / ".sx.cfg";
    libconfig::Config cfg;
    // Ignore error if unable to read config file.
    try
    {
        cfg.readFile(conf_path.native().c_str());
    }
    catch (const libconfig::FileIOException&) {}
    catch (const libconfig::ParseException&) {}
    // Read off values
    const libconfig::Setting& root = cfg.getRoot();
    get_value<std::string>(root, config, "service", "tcp://46.4.92.107:9091");
}

