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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_height__invoke)

BOOST_AUTO_TEST_CASE(fetch_height__invoke__mainnet_wait_0__failure)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_height);
    command.set_general_connect_timeout_seconds_setting(0);
    BX_REQUIRE_FAILURE(command.invoke(output, error));

    // TODO: figure out why on Windows the message is not the libbitcoin text.
    // BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(channel_timeout) + "\n");
}

BOOST_AUTO_TEST_CASE(fetch_height__invoke__mainnet__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_height);
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_CASE(fetch_height__invoke__testnet__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_height);
    command.set_general_network_setting("testnet");
    command.set_testnet_url_setting({ BX_TESTNET_SERVER });
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_CASE(fetch_height__invoke__bogus_server_url_argument__failure)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_height);
    command.set_server_url_argument("bogus");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
}

BOOST_AUTO_TEST_CASE(fetch_height__invoke__testnet_server_url_argument__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_height);
    command.set_general_network_setting("testnet");
    command.set_testnet_url_setting({ BX_TESTNET_SERVER });
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
