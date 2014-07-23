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
#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>
#include "command.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(unwrap__invoke)

BOOST_AUTO_TEST_CASE(unwrap__invoke__invalid_size_hex__failure_error)
{
    // $ sx unwrap 031bab84
    SX_DECLARE_COMMAND(unwrap);
    command.set_hex_argument({ "031bab84" });
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR(SX_UNWRAP_INVALID_SIZE "\n");
}

BOOST_AUTO_TEST_CASE(unwrap__invoke__invalid_checksum_hex__failure_error)
{
    // $ sx unwrap 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(unwrap);
    command.set_hex_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR(SX_UNWRAP_INVALID_CHECKSUM "\n");
}

BOOST_AUTO_TEST_CASE(unwrap__invoke__valid_checksum_hex__okay_output)
{
    // $ sx unwrap 2a031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006298eebe4
    SX_DECLARE_COMMAND(unwrap);
    command.set_hex_argument({ "2a031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006298eebe4" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("42 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 298eebe4\n");
}

BOOST_AUTO_TEST_SUITE_END()