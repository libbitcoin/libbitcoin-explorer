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
#include <boost/test/unit_test.hpp>
#include <sx/command/stealth-addr.hpp>
#include <sx/sx.hpp>
#include <sx/utility/console.hpp>
#include "setup.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(command_stealth_addr)

BOOST_AUTO_TEST_CASE(command_stealth_addr_invoke_expected_output)
{
    SX_DECLARE_COMMAND(stealth_addr);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("Y1abok3AUfCt\n");
}

BOOST_AUTO_TEST_CASE(command_stealth_addr_invoke_bogus_input_expected_output)
{
    SX_DECLARE_COMMAND_INPUT(stealth_addr, "bogus");
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("Y1abok3AUfCt\n");
}

BOOST_AUTO_TEST_SUITE_END()