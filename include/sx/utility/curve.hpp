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

#include <random>
#include <bitcoin/bitcoin.hpp>

using namespace bc;

ec_secret generate_random_secret();

bool set_ec_secret(ec_secret& secret, const std::string& arg);

bool set_ec_point(ec_point& point, const std::string& arg);

bool ec_math_parse_args(int argc, char** argv, ec_secret& secret,
    ec_point& point);

#endif