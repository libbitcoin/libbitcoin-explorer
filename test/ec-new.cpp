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
#include "precompile.hpp"
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(ec_new__invoke)

BOOST_AUTO_TEST_CASE(ec_new__invoke_128_bit_seed__okay_output)
{
    SX_DECLARE_COMMAND(ec_new);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8\n");
}

BOOST_AUTO_TEST_CASE(ec_new__invoke_64_bit_seed__failure_error)
{
    SX_DECLARE_COMMAND(ec_new);
    command.set_seed_argument({ "baadf00dbaadf00d" });
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    SX_REQUIRE_ERROR(SX_EC_NEW_SHORT_SEED "\n");
}

// TODO: what seed generates an invalid key so we can cover this code path?

//BOOST_AUTO_TEST_CASE(ec_new__invoke_128_bit_bad_seed__failure_error)
//{
//    SX_DECLARE_COMMAND(ec_new);
//    command.set_seed_argument({ "00000000000000000000000000000000" });
//    SX_REQUIRE_FAILURE(command.invoke(output, error));
//    SX_REQUIRE_ERROR(SX_EC_NEW_INVALID_KEY "\n");
//}

BOOST_AUTO_TEST_SUITE_END()