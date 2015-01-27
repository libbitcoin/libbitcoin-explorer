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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_stealth__invoke)

#define BX_FETCH_STEALTH_HEIGHT0_PREFIX10101010_INFO \
"stealth\n" \
"{\n" \
"    match\n" \
"    {\n" \
"        ephemeral_public_key 03c35235b93427c39f477a83c493d2ea74d9195dc8a3b3e7dbb5ad88584b1472d2\n" \
"        paid_address 1C8cs6vuuHqN7dtHqh13Yc6395unYcpSC6\n" \
"        transaction_hash d216cd6596d4119acba1b8d786cdeb15f76f01d8a3ee12603e2581950857b736\n" \
"    }\n" \
"}\n"

// TODO: need libbitcoin-server.
BOOST_AUTO_TEST_CASE(fetch_stealth__invoke_mainnet_height_0__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_stealth);
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

// TODO: need libbitcoin-server.
BOOST_AUTO_TEST_CASE(fetch_stealth__invoke_mainnet_height_323557__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_stealth);
    command.set_height_option(323557);
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

// TODO: need libbitcoin-server.
// This test is fragile, will eventually break.
BOOST_AUTO_TEST_CASE(fetch_stealth__invoke_mainnet_height_0_prefix_10101010__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_stealth);
    command.set_format_option({ "info" });
    command.set_height_option(0);
    command.set_prefix_argument({ "10101010" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_STEALTH_HEIGHT0_PREFIX10101010_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()