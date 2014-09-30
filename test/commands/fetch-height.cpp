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

BOOST_AUTO_TEST_SUITE(fetch_height__invoke)
/*
// DISABLED until client-server calls are isolated for test.

#define BX_FETCH_HEADER_TIMEOUT "timed out"
#define BX_FETCH_HEADER_MAINNET_SERVER "tcp://obelisk2.airbitz.co:9091"
#define BX_FETCH_HEADER_TESTNET_SERVER "tcp://obelisk-testnet2.airbitz.co:9091"

BOOST_AUTO_TEST_CASE(fetch_height__invoke__mainnet_wait_0__failure_error)
{
    BX_DECLARE_COMMAND(fetch_height);
    command.set_retries_option(0);
    command.set_wait_option(0);
    command.set_server_address_setting(BX_FETCH_HEADER_MAINNET_SERVER);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_FETCH_HEADER_TIMEOUT "\n");
}

BOOST_AUTO_TEST_CASE(fetch_height__invoke__mainnet__okay)
{
    BX_DECLARE_COMMAND(fetch_height);
    command.set_retries_option(0);
    command.set_wait_option(2000);
    command.set_server_address_setting(BX_FETCH_HEADER_MAINNET_SERVER);
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_CASE(fetch_height__invoke__testnet__okay)
{
    BX_DECLARE_COMMAND(fetch_height);
    command.set_retries_option(0);
    command.set_wait_option(2000);
    command.set_server_address_setting(BX_FETCH_HEADER_TESTNET_SERVER);
    BX_REQUIRE_OKAY(command.invoke(output, error));
}
*/
BOOST_AUTO_TEST_SUITE_END()