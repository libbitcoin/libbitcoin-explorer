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
BOOST_AUTO_TEST_SUITE(base58check_encode__invoke)

BOOST_AUTO_TEST_CASE(base58check_encode__invoke__hex_bogus__throws_invalid_option_value)
{
    // $ sx base58check-encode bogus
    SX_DECLARE_COMMAND(base58check_encode);
    SX_REQUIRE_INVALID_OPTION_VALUE(command.set_hex_argument({ "bogus" }));
}

BOOST_AUTO_TEST_CASE(base58check_encode__invoke__hex_zero__failure_error)
{
    // $ sx base58check-encode 00
    SX_DECLARE_COMMAND(base58check_encode);
    command.set_hex_argument({ "00" });
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR(SX_BASE58CHECK_ENCODE_NOT_IMPLEMENTED "\n");
}

BOOST_AUTO_TEST_SUITE_END()