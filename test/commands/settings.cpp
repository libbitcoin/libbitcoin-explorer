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
BOOST_AUTO_TEST_SUITE(settings__invoke)

#define BX_SETTINGS_EMPTY \
"general.retries = 0\n" \
"general.testnet = false\n" \
"general.wait = 0\n" \
"server.url = \n"

#define BX_SETTINGS_TEST_VALUES \
"general.retries = 42\n" \
"general.testnet = true\n" \
"general.wait = 7000\n" \
"server.url = https://mainnet.obelisk.net:42\n"

BOOST_AUTO_TEST_CASE(settings__invoke__empty__okay_output)
{
    BX_DECLARE_COMMAND(settings);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_EMPTY);
}

BOOST_AUTO_TEST_CASE(settings__invoke__test_values__okay_output)
{
    BX_DECLARE_COMMAND(settings);
    command.set_general_retries_setting(42);
    command.set_general_testnet_setting(true);
    command.set_general_wait_setting(7000);
    command.set_server_url_setting("https://mainnet.obelisk.net:42");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_TEST_VALUES);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
