/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
// #include "precompile.hpp"
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_height__invoke)

BOOST_AUTO_TEST_CASE(fetch_height__invoke__mainnet_wait_0__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_height);
    command.set_general_wait_setting(0);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TIMEOUT_MESSAGE "\n");
}

BOOST_AUTO_TEST_CASE(fetch_height__invoke__mainnet__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_height);
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_CASE(fetch_height__invoke__testnet__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_height);
    command.set_server_address_setting(BX_TESTNET_SERVER);
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()