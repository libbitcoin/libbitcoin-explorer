/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(ec_to_address__invoke)

BOOST_AUTO_TEST_CASE(ec_to_address__invoke__compressed_key__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_address);
    command.set_ec_public_key_argument({ "0247140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1EKJFK8kBmasFRYY3Ay9QjpJLm4vemJtC1\n");
}

BOOST_AUTO_TEST_CASE(ec_to_address__invoke__compressed_key_version_42__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_address);
    command.set_version_option(42);
    command.set_ec_public_key_argument({ "0247140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("J8Wdbser1M3fbdQB4nxXn1FLmwtYXKovfA\n");
}

BOOST_AUTO_TEST_CASE(ec_to_address__invoke__uncompressed_key__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_address);
    command.set_ec_public_key_argument({ "0447140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36e87bb04f401be3b770a0f3e2267a6c3b14a3074f6b5ce4419f1fcdc1ca4b1cb6" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("197FLrycah42jKDgfmTaok7b8kNHA7R2ih\n");
}

BOOST_AUTO_TEST_CASE(ec_to_address__invoke__uncompressed_key_version_42__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_address);
    command.set_version_option(42);
    command.set_ec_public_key_argument({ "0447140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36e87bb04f401be3b770a0f3e2267a6c3b14a3074f6b5ce4419f1fcdc1ca4b1cb6" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("J3JahRViQGWq5X5KhPSyB1YdZwBu2EQzFR\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()