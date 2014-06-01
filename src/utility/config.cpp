/*
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
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <libconfig.h++>
#include <sx/utility/config.hpp>
#include <sx/utility/environment.hpp>

namespace sx {

#define SX_DEFAULT_CONFIG_FILENAME ".sx.cfg"
#define SX_DEFAULT_OBELISK_URI "tcp://obelisk.unsystem.net:8081"

// read the spefied configuration file
bool read_config_file(libconfig::Config& config, const tpath path)
{
    // libconfig is ANSI/MBCS on Windows - no Unicode support.
    // This translates the path from Unicode to a "generic" path in
    // ANSI/MBCS, which will result in failures (if above ASCII).

    try
    {
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
        path = path / WIDE(SX_DEFAULT_CONFIG_FILENAME);
    }

    return read_config_file(config, path);
}

// get configuration settings from file w/fallbacks or defaults.
// use CZMQ program 'makecert' to generate cert/key.
void get_config(config_map_type& map)
{
    libconfig::Config config;

    // load config defaults from memory (formerly default config file)
    map["service"] = SX_DEFAULT_OBELISK_URI;
    map["client-certificate"] = SX_DEFAULT_CONFIG_FILENAME;
    map["server-public-key"] = "";

    if (read_config(config))
    {
        // load values from config file
        const libconfig::Setting& root = config.getRoot();
        get_value<std::string>(root, map, "service");
        get_value<std::string>(root, map, "client-certificate");
        get_value<std::string>(root, map, "server-public-key");
    }
}

// validate file existence and set environment SX_CFG environment variable
bool set_config_path(std::string& path)
{
    tpath config_path(path);
    libconfig::Config config;

    // actually reading the file is overkill, but we don't do it often
    if (read_config_file(config, config_path))
        return set_sx_cfg(config_path);

    return false;
}

} // sx