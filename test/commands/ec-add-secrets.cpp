/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(ec_add_secrets__invoke)

// TODO: generate overflow condition

//BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__overflow__failure_error)
//{
//    BX_DECLARE_COMMAND(ec_add_secrets);
//    command.set_secrets_argument(
//    {
//        { "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" },
//        { "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" }
//    });
//    BX_REQUIRE_FAILURE(command.invoke(output, error));
//    BX_REQUIRE_ERROR(BX_EC_ADD_SECRETS_OUT_OF_RANGE "\n");
//}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__no_value__okay_output)
{
    BX_DECLARE_COMMAND(ec_add_secrets);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0000000000000000000000000000000000000000000000000000000000000000\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__one_value__okay_output)
{
    BX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__two_same_values__okay_output)
{
    BX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("375709cd0fc6ca29dd5eb402f861a6583eb3ba9d4cc53b4f2e1946e8a27ba00c\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__three_same_values__okay_output)
{
    BX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("53028eb397aa2f3ecc0e0e04749279845e0d97ebf327d8f6c525ea5cf3b97012\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__two_secret_values__okay_output)
{
    BX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "375709cd0fc6ca29dd5eb402f861a6583eb3ba9d4cc53b4f2e1946e8a27ba00c" }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("53028eb397aa2f3ecc0e0e04749279845e0d97ebf327d8f6c525ea5cf3b97012\n");
}

BOOST_AUTO_TEST_CASE(ec_add_secrets__invoke__increment_value__okay_output)
{
    BX_DECLARE_COMMAND(ec_add_secrets);
    command.set_secrets_argument(
    {
        { "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" },
        { "0000000000000000000000000000000000000000000000000000000000000001" }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd007\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
