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
BOOST_AUTO_TEST_SUITE(fetch_header__invoke)

#define FETCH_HEADER_GENESIS_INFO \
"bits 486604799\n" \
"hash 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f\n" \
"merkle_tree_hash 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n" \
"nonce 2083236893\n" \
"previous_block_hash 0000000000000000000000000000000000000000000000000000000000000000\n" \
"time_stamp 1231006505\n" \
"version 1\n"
#define FETCH_HEADER_SECOND_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<bits>486604799</bits><hash>00000000839a8e6886ab5951d76f411475428afc90947ee320161bbf18eb6048</hash><merkle_tree_hash>0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098</merkle_tree_hash><nonce>2573394689</nonce><previous_block_hash>000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f</previous_block_hash><time_stamp>1231469665</time_stamp><version>1</version>"

BOOST_AUTO_TEST_CASE(fetch_header__invoke__mainnet_block_height_0_native__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_header);
    command.set_height_option(0);
    command.set_format_option({ "native" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_HEADER_GENESIS_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_header__invoke__mainnet_block_height_2_xml__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_header);
    command.set_height_option(1);
    command.set_format_option({ "xml" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_HEADER_SECOND_XML);
}

BOOST_AUTO_TEST_CASE(fetch_header__invoke__mainnet_block_hash_genesis_info__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_header);
    command.set_hash_option({ BX_GENESIS_BLOCK_HASH });
    command.set_format_option({ "info" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_HEADER_GENESIS_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_header__invoke__mainnet_block_height_42_block_hash_genesis_info__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_header);
    command.set_height_option(42);
    command.set_format_option({ "info" });
    command.set_hash_option({ BX_GENESIS_BLOCK_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_HEADER_GENESIS_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()