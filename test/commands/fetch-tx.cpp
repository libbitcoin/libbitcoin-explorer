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
BOOST_AUTO_TEST_SUITE(fetch_tx__invoke)

#define FETCH_TX_SATOSHIS_WORDS_TX_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<transaction><hash>4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b</hash><inputs><input><address_hash>5b19778555f776292926b8dd581e1b9d2ab7cbbb</address_hash><previous_output><hash>0000000000000000000000000000000000000000000000000000000000000000</hash><index>4294967295</index></previous_output><script>[ffff001d] [04] [5468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73]</script><sequence>4294967295</sequence></input></inputs><lock_time>0</lock_time><outputs><output><address_hash>62e907b15cbf27d5425399ebf6f0fb50ebb88f18</address_hash><script>[04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f] checksig</script><value>5000000000</value></output></outputs><version>1</version></transaction>\n"

#define FETCH_TX_SATOSHIS_WORDS_TX_INFO \
"transaction\n" \
"{\n" \
"    hash 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            address_hash 5b19778555f776292926b8dd581e1b9d2ab7cbbb\n" \
"            previous_output\n" \
"            {\n" \
"                hash 0000000000000000000000000000000000000000000000000000000000000000\n" \
"                index 4294967295\n" \
"            }\n" \
"            script \"[ffff001d] [04] [5468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73]\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address_hash 62e907b15cbf27d5425399ebf6f0fb50ebb88f18\n" \
"            script \"[04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f] checksig\"\n" \
"            value 5000000000\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

#define FETCH_TX_SECOND_TX_HASH \
"0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098"

#define FETCH_TX_SECOND_TX_INFO \
"transaction\n" \
"{\n" \
"    hash 0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            address_hash 6d4c0aa972c314840ac07be96c5dde9c714c9ca4\n" \
"            previous_output\n" \
"            {\n" \
"                hash 0000000000000000000000000000000000000000000000000000000000000000\n" \
"                index 4294967295\n" \
"            }\n" \
"            script \"[ffff001d] [04]\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address_hash 119b098e2e980a229e139a9ed01a469e518e6f26\n" \
"            script \"[0496b538e853519c726a2c91e61ec11600ae1390813a627c66fb8be7947be63c52da7589379515d4e0a604f8141781e62294721166bf621e73a82cbf2342c858ee] checksig\"\n" \
"            value 5000000000\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

#define FETCH_TX_TESTNET_TX_HASH \
"3fe5373efdada483b5fa7bdf2249d8274f1b8c04ab5a98bce3edfb732d8e2f86"

#define FETCH_TX_TESTNET_TX_INFO \
"transaction\n" \
"{\n" \
"    hash 3fe5373efdada483b5fa7bdf2249d8274f1b8c04ab5a98bce3edfb732d8e2f86\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            address_hash 4e4158ea8b7d6fbebe998dd00af1463e5ef1b882\n" \
"            previous_output\n" \
"            {\n" \
"                hash 184256d92cb47d96e1e19747e46ee1c0db73cb8fab054989c2974d8282ec22c4\n" \
"                index 1\n" \
"            }\n" \
"            script \"[3046022100f18c97457e00c491d3eed5d9c2c5da33398595adf2708a07f677fb1e3eeeccba022100dc5c886192a9af7a28ab7689e766f3be6b01b61a4c675c97e8d2c99cd8b9d13201] [037928262812eb9e73b9ca8039f8023db84b0a86c5caf6bc28cefb85e9943684ac]\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address_hash 05e18e90cf803e17b9fa70abd2ad931389cc2cd4\n" \
"            script \"dup hash160 [05e18e90cf803e17b9fa70abd2ad931389cc2cd4] equalverify checksig\"\n" \
"            value 283979941\n" \
"        }\n" \
"        output\n" \
"        {\n" \
"            address_hash 8f3441dd22b15a30dcde56f9b3de7a61b7a3a740\n" \
"            script \"dup hash160 [8f3441dd22b15a30dcde56f9b3de7a61b7a3a740] equalverify checksig\"\n" \
"            value 475608021\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

#define FETCH_TX_TESTNET_SERIALIZED_DATA \
"0100000001c422ec82824d97c2894905ab8fcb73dbc0e16ee44797e1e1967db42cd9564218010000006c493046022100f18c97457e00c491d3eed5d9c2c5da33398595adf2708a07f677fb1e3eeeccba022100dc5c886192a9af7a28ab7689e766f3be6b01b61a4c675c97e8d2c99cd8b9d1320121037928262812eb9e73b9ca8039f8023db84b0a86c5caf6bc28cefb85e9943684acffffffff02a530ed10000000001976a91405e18e90cf803e17b9fa70abd2ad931389cc2cd488acd533591c000000001976a9148f3441dd22b15a30dcde56f9b3de7a61b7a3a74088ac00000000\n"

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_satoshis_words_tx_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_tx);
    command.set_format_option({ "info" });
    command.set_hash_argument({ BX_SATOSHIS_WORDS_TX_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_SATOSHIS_WORDS_TX_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_satoshis_words_tx_xml__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_tx);
    command.set_format_option({ "xml" });
    command.set_hash_argument({ BX_SATOSHIS_WORDS_TX_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_SATOSHIS_WORDS_TX_XML);
}

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_second_tx_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_tx);
    command.set_format_option({ "info" });
    command.set_hash_argument({ FETCH_TX_SECOND_TX_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_SECOND_TX_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__testnet_tx_info__okay_output)
{
    BX_DECLARE_CLIENT_TESTNET_COMMAND(fetch_tx);
    command.set_format_option({ "info" });
    command.set_hash_argument({ FETCH_TX_TESTNET_TX_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_TESTNET_TX_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__testnet_tx_data__okay_output)
{
    BX_DECLARE_CLIENT_TESTNET_COMMAND(fetch_tx);
    command.set_format_option({ "data" });
    command.set_hash_argument({ FETCH_TX_TESTNET_TX_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_TESTNET_SERIALIZED_DATA);
}

// Requires server of at least v3.4.
BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_second_tx_witness__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_tx);
    command.set_witness_option(true);
    command.set_format_option({ "info" });
    command.set_hash_argument({ FETCH_TX_SECOND_TX_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_SECOND_TX_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
