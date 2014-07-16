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
BOOST_AUTO_TEST_SUITE(ec_multiply_secrets__invoke)

//BOOST_AUTO_TEST_CASE(ec_multiply_secrets__invoke__overflow__failure_error)
//{
//    // $ sx ec-multiply-secrets ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
//    SX_DECLARE_COMMAND(ec_multiply_secrets);
//    command.set_secrets_argument(
//    {
//        { "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" },
//        { "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" }
//    });
//    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
//    SX_REQUIRE_ERROR(SX_EC_MULITPLY_SECRETS_OUT_OF_RANGE "\n");
//}

BOOST_AUTO_TEST_CASE(ec_multiply_secrets__invoke__one_value__okay_output)
{
    // $ sx ec-multiply-secrets 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(ec_multiply_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    auto foo = output.str();
    SX_REQUIRE_OUTPUT("1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n");
}

BOOST_AUTO_TEST_CASE(ec_multiply_secrets__invoke__two_same_values__okay_output)
{
    // $ sx ec-multiply-secrets 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(ec_multiply_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("e5b87c7917f8414d2fa5caa32ea61b06fca755fee6a113179db70f5e0d5393ba\n");
}

BOOST_AUTO_TEST_CASE(ec_multiply_secrets__invoke__three_same_values__okay_output)
{
    // $ sx ec-multiply-secrets 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(ec_multiply_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("1da46d54db3e774fe81dfeea880677b805d2ce041c1e2011b6362ee11df132d8\n");
}

BOOST_AUTO_TEST_CASE(ec_multiply_secrets__invoke__two_unique_values__okay_output)
{
    // $ sx ec-multiply-secrets 4242424242424242424242424242424242424242424242424242424242424242 0000000000000000000000000000000000000000000000000000000000000001
    SX_DECLARE_COMMAND(ec_multiply_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "0000000000000000000000000000000000000000000000000000000000000001" }
    });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n");
}

BOOST_AUTO_TEST_SUITE_END()