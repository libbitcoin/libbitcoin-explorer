#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <libconfig.h++>
#include "config.hpp"
#include "environment.hpp"

template <typename T>
void get_value(const libconfig::Setting& root, config_map_type& config_map,
    const std::string& key_name, const T& fallback_value)
{
    T value;

    // libconfig is ANSI/MBCS on Windows - no Unicode support.
    // This reads ANSI/MBCS values from config. If they are UTF-8 (and above
    // the ASCII band) the values will be misinterpreted upon use.
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

void initialize_config(libconfig::Config& configuration)
{
    tstring environment_path = sx_config_path();
    tpath config_path = environment_path.empty() ?
        tpath(home_directory()) / L".sx.cfg" :
        tpath(environment_path);
    set_config_path(configuration, config_path.generic_string().c_str());
}

void load_config(config_map_type& config_map)
{
    libconfig::Config configuration;
    initialize_config(configuration);

    // Read off values.
    const libconfig::Setting& root = configuration.getRoot();
    get_value<std::string>(root, config_map, "service", OBELISK_SERVICE_URI);
    get_value<std::string>(root, config_map, "client-certificate", ".sx.cert");
    get_value<std::string>(root, config_map, "server-public-key", "");
}
