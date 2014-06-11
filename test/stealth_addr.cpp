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
#include "setup.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(stealth_addr__invoke)

// TODO: integral types must be initialized for unit tests since 
// program_options does not do it.

BOOST_AUTO_TEST_CASE(default_input__expected_output)
{
    SX_DECLARE_COMMAND(stealth_addr);
    command.set_reuse_key_option(false);
    command.set_signatures_option(0);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("Y1QsNeLdxLo6\n");
}

BOOST_AUTO_TEST_CASE(bogus_input__expected_output)
{
    SX_DECLARE_COMMAND_INPUT(stealth_addr, "bogus");
    command.set_reuse_key_option(false);
    command.set_signatures_option(0);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("Y1QsNeLdxLo6\n");
}

BOOST_AUTO_TEST_CASE(signatures_four__expected_output)
{
    SX_DECLARE_COMMAND(stealth_addr);
    command.set_signatures_option(4);
    command.set_reuse_key_option(false);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("Y1QsQdtFq3a8\n");
}

BOOST_AUTO_TEST_CASE(reuse_key__expected_output)
{
    // stealth_addr -r -s 4 scan1
    SX_DECLARE_COMMAND(stealth_addr);
    command.set_signatures_option(4);
    command.set_reuse_key_option(true);
    command.set_scan_pubkey_argument("scan1");
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("Y1aa69Z9G1gu\n");
}

BOOST_AUTO_TEST_SUITE_END()

//BOOST_AUTO_TEST_SUITE(stealth_addr__nop)
//
//BOOST_AUTO_TEST_CASE(always__is_true)
//{
//    BOOST_REQUIRE(true);
//}
//
//BOOST_AUTO_TEST_SUITE_END()