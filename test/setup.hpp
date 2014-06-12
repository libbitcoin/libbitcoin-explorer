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
#ifndef SETUP_HPP
#define SETUP_HPP

#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>

#define SX_USING_NAMESPACES()
using namespace std; \
using namespace sx; \
using namespace sx::extensions;

#define _SX_DECLARE_COMMAND(extension) \
    stringstream output; \
    stringstream error; \
    extension command
#define SX_DECLARE_COMMAND(extension) \
    stringstream input; \
    _SX_DECLARE_COMMAND(extension)
#define SX_DECLARE_COMMAND_INPUT(extension, value) \
    stringstream input(value); \
    _SX_DECLARE_COMMAND(extension)

// console results
#define SX_REQUIRE_OKAY(value) BOOST_REQUIRE(value == console_result::okay)
#define SX_REQUIRE_FAILURE(value) BOOST_REQUIRE(value == console_result::failure)
#define SX_REQUIRE_INVALID(value) BOOST_REQUIRE(value == console_result::invalid)

// stream results
#define SX_REQUIRE_ERROR(value) BOOST_REQUIRE(error.str() == value)
#define SX_REQUIRE_OUTPUT(value) BOOST_REQUIRE(output.str() == value)

#endif