#ifndef SX_CONFIG_HPP
#define SX_CONFIG_HPP

#include <map>
#include <string>

#define OBELISK_SERVICE_URI "tcp://37.139.11.99:9091"

typedef std::map<std::string, std::string> config_map_type;

void load_config(config_map_type& config_map);

#endif