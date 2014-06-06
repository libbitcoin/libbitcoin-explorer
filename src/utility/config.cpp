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
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <libconfig.h++>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/environment.hpp>

namespace sx {

// unfortunately testnet is compiled into libbitcoin, so we have no choice but
// to use the same value as the library we are linking to or we may encounter
// problems. once libbitcoin and libwallet are modified to externalize that
// option we could have more flexibility.
#ifdef ENABLE_TESTNET
    #define SX_DEFAULT_TESTNET "true"
#else
    #define SX_DEFAULT_TESTNET "false"
#endif

// the choice of a server (and therefore its public key) is restricted by the
// testnet configuration of this build.
#define SX_DEFAULT_SERVICE "tcp://obelisk.unsystem.net:8081"
#define SX_DEFAULT_SERVER_PUBLIC_KEY ""

// a client certificate allows a client to be identified by the server, however
// this requires the server to have issued the client cert or to at least trust
// that it has the client's public key. this may be useful in administrative
// contexts but not as much in wallet contexts, which generally prefer 
// anonymity to strong identification.
#define SX_DEFAULT_CLIENT_CERTIFICATE ".sx.cfg"

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
        path = path / WIDE(SX_DEFAULT_CLIENT_CERTIFICATE);
    }

    return read_config_file(config, path);
}

// get configuration settings from file w/fallbacks or defaults.
// Users should use CZMQ program 'makecert' to generate cert/key.
void get_config(config_map_type& map)
{
    libconfig::Config config;

    // load config defaults from memory (formerly default config file)
    // these are split out to handle the case where the file doesn't exist
    // yet we still need to load config, as we should be able to initialize
    // without forcing the creation of a config file full of defaults.
    map[SX_SETTING_TESTNET] = SX_DEFAULT_TESTNET;
    map[SX_SETTING_SERVICE] = SX_DEFAULT_SERVICE;
    map[SX_SETTING_SERVER_PUBLIC_KEY] = SX_DEFAULT_SERVER_PUBLIC_KEY;
    map[SX_SETTING_CLIENT_CERTIFICATE] = SX_DEFAULT_CLIENT_CERTIFICATE;

    if (read_config(config))
    {
        // load typed values from config file into our string-to-string mapping
        const libconfig::Setting& root = config.getRoot();
        get_value<bool>(root, map, SX_SETTING_TESTNET);
        get_value<std::string>(root, map, SX_SETTING_SERVICE);
        get_value<std::string>(root, map, SX_SETTING_SERVER_PUBLIC_KEY);
        get_value<std::string>(root, map, SX_SETTING_CLIENT_CERTIFICATE);
    }
}

// validate file existence and set environment SX_CFG environment variable
bool set_config_path(const std::string& path)
{
    tpath config_path(path);
    libconfig::Config config;

    // actually reading the file is overkill, but we don't do it often
    if (read_config_file(config, config_path))
        return set_sx_cfg(config_path);

    return false;
}

} // sx