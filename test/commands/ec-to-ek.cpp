/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(ec_to_ek__invoke)

#ifdef WITH_ICU

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__vector_0_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5" });
    command.set_passphrase_argument("TestingOneTwoThree");
    command.set_uncompressed_option(true);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__vector_1_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae" });
    command.set_passphrase_argument("Satoshi");
    command.set_uncompressed_option(true);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRNFFkZc2NZ6dJqFfhRoFNMR9Lnyj7dYGrzdgXXVMXcxoKTePPX1dWByq\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__vector_2__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5" });
    command.set_passphrase_argument("TestingOneTwoThree");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYNKZ1EAgYgmQfmNVamxyXVWHzK5s6DGhwP4J5o44cvXdoY7sRzhtpUeo\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__vector_3__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae" });
    command.set_passphrase_argument("Satoshi");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYLtMnXvfG3oJde97zRyLYFZCYizPU5T3LwgdYJz1fRhh16bU7u6PPmY7\n");
}

#else // WITH_ICU

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__not_icu__failure_error)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_TO_EK_REQUIRES_ICU "\n");
}

#endif // !WITH_ICU

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
