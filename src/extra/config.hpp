#ifndef OBELISK_WORKER_CONFIG_HPP
#define OBELISK_WORKER_CONFIG_HPP

#include <map>
#include <string>

typedef std::map<std::string, std::string> config_map_type;
void load_config(config_map_type& config);

#endif

