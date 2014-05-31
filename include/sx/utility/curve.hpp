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

/**
 * Generate a random secret using the default random engine.
 *
 * @return  The new secret.
 */
bc::ec_secret generate_random_secret();

/**
 * Parse command line args for a secret and a point.
 * Searches every argument and returns the last secret and the last point
 * discovered.
 *
 * @param[in]  argc    The count of arguments in the argument array.
 * @param[in]  argv    The argument array.
 * @param[out] secret  The parsed secret.
 * @param[out] point   The parsed point.
 * @return             True if a secret and a point have been returned.
 */
bool ec_math_parse_args(const int argc, const char* argv[], 
    bc::ec_secret& secret, bc::ec_point& point);

/**
 * Parse a point from the specified argument.
 *
 * @param[out] point   The parsed point.
 * @param[in]  arg     The argument to parse.
 * @return             True if a point has been returned.
 */
bool set_ec_point(bc::ec_point& point, const std::string& arg);

/**
 * Parse a secret from the specified argument.
 *
 * @param[out] secret  The parsed secret.
 * @param[in]  arg     The argument to parse.
 * @return             True if a secret has been returned.
 */
bool set_ec_secret(bc::ec_secret& secret, const std::string& arg);

} // sx

#endif