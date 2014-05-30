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
#ifndef SX_CONFIG_HPP
#define SX_CONFIG_HPP

#include <map>
#include <string>
#include <libconfig.h++>
#include "utility/compat.hpp"

#define OBELISK_DEFAULT_URI "tcp://obelisk.unsystem.net:8081"

typedef std::map<std::string, std::string> config_map_type;

// read the spefied configuration file setting
template <typename T>
void get_value(const libconfig::Setting& root, config_map_type& map,
    const std::string& key);

// read the spefied configuration file
bool read_config_file(libconfig::Config& config, tpath path);

// determine the proper configuration file path and read the file
bool read_config(libconfig::Config& config);

// get configuration settings from file w/fallbacks or defaults.
// use CZMQ program 'makecert' to generate cert/key.
void get_config(config_map_type& map);

// validate file existence and set environment SX_CFG environment variable
bool set_config_path(std::string& path);

#endif