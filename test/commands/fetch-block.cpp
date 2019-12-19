/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(fetch_block__invoke)

#define FETCH_BLOCK_GENESIS_INFO \
"block\n" \
"{\n" \
"    bits 486604799\n" \
"    hash 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f\n" \
"    merkle_root 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n" \
"    nonce 2083236893\n" \
"    previous_block_hash 0000000000000000000000000000000000000000000000000000000000000000\n" \
"    time_stamp 1231006505\n" \
"    version 1\n" \
"    transactions\n" \
"    {\n" \
"        transaction\n" \
"        {\n" \
"            hash 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n" \
"            inputs\n" \
"            {\n" \
"                input\n" \
"                {\n" \
"                    address_hash 5b19778555f776292926b8dd581e1b9d2ab7cbbb\n" \
"                    previous_output\n" \
"                    {\n" \
"                        hash 0000000000000000000000000000000000000000000000000000000000000000\n" \
"                        index 4294967295\n" \
"                    }\n" \
"                    script \"[ffff001d] [04] [5468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73]\"\n" \
"                    sequence 4294967295\n" \
"                }\n" \
"            }\n" \
"            lock_time 0\n" \
"            outputs\n" \
"            {\n" \
"                output\n" \
"                {\n" \
"                    address_hash 62e907b15cbf27d5425399ebf6f0fb50ebb88f18\n" \
"                    script \"[04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f] checksig\"\n" \
"                    value 5000000000\n" \
"                }\n" \
"            }\n" \
"            version 1\n" \
"        }\n" \
"    }\n" \
"}\n" \

#define FETCH_BLOCK_ONE_XML                \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<block><bits>486604799</bits><hash>00000000839a8e6886ab5951d76f411475428afc90947ee320161bbf18eb6048</hash><merkle_root>0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098</merkle_root><nonce>2573394689</nonce><previous_block_hash>000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f</previous_block_hash><time_stamp>1231469665</time_stamp><version>1</version><transactions><transaction><hash>0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098</hash><inputs><input><address_hash>6d4c0aa972c314840ac07be96c5dde9c714c9ca4</address_hash><previous_output><hash>0000000000000000000000000000000000000000000000000000000000000000</hash><index>4294967295</index></previous_output><script>[ffff001d] [04]</script><sequence>4294967295</sequence></input></inputs><lock_time>0</lock_time><outputs><output><address_hash>119b098e2e980a229e139a9ed01a469e518e6f26</address_hash><script>[0496b538e853519c726a2c91e61ec11600ae1390813a627c66fb8be7947be63c52da7589379515d4e0a604f8141781e62294721166bf621e73a82cbf2342c858ee] checksig</script><value>5000000000</value></output></outputs><version>1</version></transaction></transactions></block>\n"

#define BX_GENESIS_BLOCK_HASH "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"

BOOST_AUTO_TEST_CASE(fetch_block__invoke__mainnet_block_height_0_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_block);
    command.set_height_option(0);
    command.set_format_option({ "info" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_BLOCK_GENESIS_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_block__invoke__mainnet_block_height_1_xml__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_block);
    command.set_height_option(1);
    command.set_format_option({ "xml" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_BLOCK_ONE_XML);
}

BOOST_AUTO_TEST_CASE(fetch_block__invoke__mainnet_block_hash_genesis_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_block);
    command.set_hash_option({ BX_GENESIS_BLOCK_HASH });
    command.set_format_option({ "info" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_BLOCK_GENESIS_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_block__invoke__mainnet_block_height_42_block_hash_genesis_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_block);
    command.set_height_option(42);
    command.set_format_option({ "info" });
    command.set_hash_option({ BX_GENESIS_BLOCK_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_BLOCK_GENESIS_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
