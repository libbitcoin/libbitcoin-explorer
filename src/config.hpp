#ifndef SX_CONFIG_HPP
#define SX_CONFIG_HPP

#include <map>
#include <string>

// TODO: determine if we should have both of these.
#define OBELISK_DEFAULT_URI "tcp://obelisk.unsystem.net:8081"
#define OBELISK_FALLBACK_URI "tcp://37.139.11.99:9091"

typedef std::map<std::string, std::string> config_map_type;

void get_config(config_map_type& map);
bool set_config_path(std::string& path);

#endif