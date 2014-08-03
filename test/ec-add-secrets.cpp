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
BOOST_AUTO_TEST_SUITE(ec_add_secrets__invoke)

// TODO: generate overflow condition
//BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__overflow__failure_error)
//{
//    // $ sx ec-add-secrets ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
//    SX_DECLARE_COMMAND(ec_add_secrets);
//    command.set_secrets_argument(
//    {
//        { "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" },
//        { "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" }
//    });
//    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
//    SX_REQUIRE_ERROR(SX_EC_ADD_SECRETS_OUT_OF_RANGE "\n");
//}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__no_value__okay_output)
{
    // $ sx ec-add-secrets
    SX_DECLARE_COMMAND(ec_add_secrets);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("0000000000000000000000000000000000000000000000000000000000000000\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__one_value__okay_output)
{
    // $ sx ec-add-secrets 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__two_same_values__okay_output)
{
    // $ sx ec-add-secrets 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("375709cd0fc6ca29dd5eb402f861a6583eb3ba9d4cc53b4f2e1946e8a27ba00c\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__three_same_values__okay_output)
{
    // $ sx ec-add-secrets 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("53028eb397aa2f3ecc0e0e04749279845e0d97ebf327d8f6c525ea5cf3b97012\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__two_unique_values__okay_output)
{
    // $ sx ec-add-secrets 4242424242424242424242424242424242424242424242424242424242424242 0000000000000000000000000000000000000000000000000000000000000001
    SX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "0000000000000000000000000000000000000000000000000000000000000001" }
    });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd007\n");
}

BOOST_AUTO_TEST_SUITE_END()