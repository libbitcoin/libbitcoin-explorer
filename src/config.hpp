#ifndef SX_CONFIG_HPP
#define SX_CONFIG_HPP

#include <map>
#include <string>

#define OBELISK_DEFAULT_URI "tcp://obelisk.unsystem.net:8081"

typedef std::map<std::string, std::string> config_map_type;

void get_config(config_map_type& map);
bool set_config_path(std::string& path);

#endif