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
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(ec_multiply__invoke)

// TODO: generate overflow condition
//BOOST_AUTO_TEST_CASE(ec_multiply__invoke__overflow__failure_error)
//{
//    // $ sx ec-multiply 02ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
//    SX_DECLARE_COMMAND(sx::extension::ec_multiply);
//    command.set_point_argument({ "02ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
//    command.set_secret_argument({ "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
//    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
//    SX_REQUIRE_ERROR(SX_EC_MULITPLY_OUT_OF_RANGE "\n");
//}

BOOST_AUTO_TEST_CASE(ec_multiply__invoke__add_values__okay_output)
{
    // $ sx ec-multiply 021bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(sx::extension::ec_multiply);
    command.set_point_argument({ "021bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    command.set_secret_argument({ "1bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("02da5629b7902abcfc166b30eda4cc6b2702b5d0bb867217614101caa710f0753b\n");
}

BOOST_AUTO_TEST_SUITE_END()