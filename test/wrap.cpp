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
BOOST_AUTO_TEST_SUITE(wrap__invoke)

BOOST_AUTO_TEST_CASE(unwrap__invoke__bogus_hex__throws_invalid_option_value)
{
    // $ sx wrap bogus
    SX_DECLARE_COMMAND(unwrap);
    SX_REQUIRE_INVALID_OPTION_VALUE(command.set_hex_argument({ "bogus" }));
}

BOOST_AUTO_TEST_CASE(wrap__invoke__valid_hex_version__okay_output)
{
    // $ sx wrap 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(wrap);
    command.set_version_option(42);
    command.set_hex_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("2a031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006298eebe4\n");
}

BOOST_AUTO_TEST_SUITE_END()