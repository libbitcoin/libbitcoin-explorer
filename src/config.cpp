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

// read the spefied configuration file
bool read_config_file(libconfig::Config& config, tpath path)
{
    try
    {
        // libconfig is ANSI/MBCS on Windows - no Unicode support.
        // This translates the path from Unicode to a "generic" path in
        // ANSI/MBCS, which can result in failures if above ASCII.
        config.readFile(path.generic_string().c_str());
        return true;
    }
    catch (const libconfig::FileIOException&) {}
    catch (const libconfig::ParseException&) {}
    return false;
}

// determine the proper configuration file path and read the file
bool read_config(libconfig::Config& config)
{
    tpath path(get_sx_cfg());
    if (path.empty())
    {
        path = home_directory();
        if (path.empty())
            return false;
        path = path / L".sx.cfg";
    }

    return read_config_file(config, path);
}

// get configuration settings from file w/fallbacks or defaults
void get_config(config_map_type& map)
{
    libconfig::Config config;

    if (read_config(config))
    {
        // load values from config file, with fallbacks
        const libconfig::Setting& root = config.getRoot();
        get_value<std::string>(root, map, "service", OBELISK_FALLBACK_URI);
        get_value<std::string>(root, map, "client-certificate", ".sx.cert");
        get_value<std::string>(root, map, "server-public-key", "");;
    }
    else
    {
        // load config defaults from memory.
        map["service"] = OBELISK_DEFAULT_URI;
        map["client-certificate"] = ".sx.cert";
        map["server-public-key"] = "";

        //# ~/.sx.cfg Sample file.
        //service = "tcp://obelisk.unsystem.net:8081"
        //# Use CZMQ program 'makecert' to generate these values.
        //#client - certificate = "/home/genjix/.sx.cert"
        //#server - public - key = "W=GRFxHUuUN#En3MI]f{}X:KWnV=pRZ$((byg=:h"
        //#testnet = "false"
    }
}

// validate file existence and set environment SX_CFG environment variable
bool set_config_path(std::string& path)
{
    tpath config_path(path);
    libconfig::Config config;

    // reading the file is overkill, but we don't do it often
    if (!read_config_file(config, config_path))
        return false;

    set_sx_cfg(config_path);
    return true;
}
