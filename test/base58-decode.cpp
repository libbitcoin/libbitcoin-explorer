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
BOOST_AUTO_TEST_SUITE(base58_decode__invoke)

BOOST_AUTO_TEST_CASE(base58_decode__invoke__bogus_value__throws_invalid_option_value)
{
    // $ sx base58-decode "?? --*&^aa !"
    SX_DECLARE_COMMAND(base58_decode);
    SX_REQUIRE_INVALID_OPTION_VALUE(command.set_base58_argument({ "?? --*&^aa !" }));
}

BOOST_AUTO_TEST_CASE(base58_decode__invoke__valid_value__okay_output)
{
    // $ sx base58-decode somebase58text
    SX_DECLARE_COMMAND(base58_decode);
    command.set_base58_argument({ "somebase58text" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("03885215aefaf0f35ad805\n");
}

BOOST_AUTO_TEST_SUITE_END()