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
#ifndef SX_CURVE_HPP
#define SX_CURVE_HPP

#include <bitcoin/bitcoin.hpp>

namespace sx {
using namespace bc;

/**
 * Generate a random secret using the default random engine.
 *
 * @return The new secret.
 */
ec_secret generate_random_secret();

/**
 * Parse command line args for a secret and a point.
 * Searches every argument and returns the last secret and the last point
 * discovered.
 *
 * @param argc the count of arguments in the argument array.
 * @param argv the argument array.
 * @param secret the parsed secret.
 * @param point the parsed point.
 * @return True if a secret and a point have been returned.
 */
bool ec_math_parse_args(const int argc, const char* argv[], 
    ec_secret& secret, ec_point& point);

/**
 * Parse a point from the specified argument.
 *
 * @param point the parsed point.
 * @param arg the argument to parse.
 * @return True if a point has been returned.
 */
bool set_ec_point(ec_point& point, const std::string& arg);

/**
 * Parse a secret from the specified argument.
 *
 * @param secret the parsed secret.
 * @param arg the argument to parse.
 * @return True if a secret has been returned.
 */
bool set_ec_secret(ec_secret& secret, const std::string& arg);

} // sx

#endif