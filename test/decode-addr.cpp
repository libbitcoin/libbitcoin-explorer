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
#include <boost/format.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>
#include "command.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(decode_addr__invoke)

BOOST_AUTO_TEST_CASE(decode_addr__invoke__bogus_value__failure_error)
{
    // $ sx decode-addr "?? --*&^aa !"
    SX_DECLARE_COMMAND(decode_addr);
    command.set_address_argument({ "?? --*&^aa !" });
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    stringstream err;
    err << boost::format(SX_DECODE_ADDR_INVALID_ADDRESS) % "?? --*&^aa !";
    SX_REQUIRE_ERROR(err.str() + "\n");
}

BOOST_AUTO_TEST_CASE(decode_addr__invoke__valid_value__okay_output)
{
    // $ sx decode-addr 3J98t1WpEZ73CNmQviecrnyiWrnqRhWNLy
    SX_DECLARE_COMMAND(decode_addr);
    command.set_address_argument({ "3J98t1WpEZ73CNmQviecrnyiWrnqRhWNLy" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\n");
}

BOOST_AUTO_TEST_SUITE_END()