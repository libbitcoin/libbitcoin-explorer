#ifndef SX_ENVIRONMENT_HPP
#define SX_ENVIRONMENT_HPP

#include <boost/filesystem.hpp>
#include "compat.hpp"

tstring home_directory();
tstring get_sx_cfg();
bool set_sx_cfg(tpath& path);

#endif