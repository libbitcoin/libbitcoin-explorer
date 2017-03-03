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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_stealth__invoke)

#define BX_FETCH_STEALTH_HEIGHT0_PREFIX10101010101010101_INFO \
"stealth\n" \
"{\n" \
"    match\n" \
"    {\n" \
"        ephemeral_public_key 0269643f3c59cd5a00bd6b016e3748db7251fbae08310a8721a07e6575fc5d578d\n" \
"        public_key_hash 0c2bb37c64f938ccaeb86be640ef8a743ec98cda\n" \
"        transaction_hash 4c436b565e87c9042476d3a1bed0114443803645e10821db63c59643c85f1497\n" \
"    }\n" \
"    match\n" \
"    {\n" \
"        ephemeral_public_key 02d1878fc4b1bf78852f48540fcf5f3efef65d518250a057db5a36283586deb50f\n" \
"        public_key_hash b980c018bcb7ad6fcfacfa5d7d474a7f586fb926\n" \
"        transaction_hash 98bf476c8d8b58c64373f25413327ea5666e6d97793f14bd14cb1072d16702bf\n" \
"    }\n" \
"}\n"

// requires libbitcoin-server.
BOOST_AUTO_TEST_CASE(fetch_stealth__invoke_mainnet_height_400000__okay)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_stealth);
    command.set_height_option(400000);
    command.set_filter_argument({ "101010101010101010" });
    command.set_server_url_setting({ BX_MAINNET_SERVER });
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

// requires libbitcoin-server.
BOOST_AUTO_TEST_CASE(fetch_stealth__invoke_mainnet_height_0_prefix_10101010101010101__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_stealth);
    command.set_format_option({ "info" });
    command.set_height_option(0);
    command.set_filter_argument({ "10101010101010101" });
    command.set_server_url_setting({ BX_MAINNET_SERVER });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    // Disabled due to network variability.
    ////BX_REQUIRE_OUTPUT(BX_FETCH_STEALTH_HEIGHT0_PREFIX10101010101010101_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
