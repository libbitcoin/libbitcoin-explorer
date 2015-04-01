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

// TODO: determine why the paid_address changed from 1AEDp5EtdMg9ZUZhyB47ZZupwfdVCnG5bS to mpkB78KsSP7QLb3Kgk2VPV89ofEC73bqD6.
#define BX_FETCH_STEALTH_HEIGHT0_PREFIX10101010101_INFO \
"stealth\n" \
"{\n" \
"    match\n" \
"    {\n" \
"        ephemeral_public_key 024f4101000199071b753d68747470733a2f2f6370722e736d2f50647334476956\n" \
"        paid_address mpkB78KsSP7QLb3Kgk2VPV89ofEC73bqD6\n" \
"        transaction_hash 2b8024d6d4c1c333ecd8d0d8af44aed676c8624cf1503340b37e9465cad415f5\n" \
"    }\n" \
"}\n"

// requires libbitcoin-server.
BOOST_AUTO_TEST_CASE(fetch_stealth__invoke_mainnet_height_0__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_stealth);
    command.set_mainnet_url_setting({ BX_MAINNET_SERVER });
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

// requires libbitcoin-server.
BOOST_AUTO_TEST_CASE(fetch_stealth__invoke_mainnet_height_323557__okay)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_stealth);
    command.set_height_option(323557);
    command.set_mainnet_url_setting({ BX_MAINNET_SERVER });
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

// requires libbitcoin-server.
// This test is fragile, will eventually break.
BOOST_AUTO_TEST_CASE(fetch_stealth__invoke_mainnet_height_0_prefix_10101010101__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_stealth);
    command.set_format_option({ "info" });
    command.set_height_option(0);
    command.set_prefix_argument({ "10101010101" });
    command.set_mainnet_url_setting({ BX_MAINNET_SERVER });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_STEALTH_HEIGHT0_PREFIX10101010101_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()