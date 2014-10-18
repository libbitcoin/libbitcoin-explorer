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
BOOST_AUTO_TEST_SUITE(fetch_tx__invoke)

#define FETCH_TX_SATOSHIS_WORDS_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<transaction><hash>4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b</hash><inputs><input><previous_output>0000000000000000000000000000000000000000000000000000000000000000:4294967295</previous_output><script>[ 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73 ]</script><sequence>4294967295</sequence></input></inputs><lock_time>0</lock_time><outputs><output><address>1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa</address><script>[ 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f ] checksig</script><value>5000000000</value></output></outputs><version>1</version></transaction>"
#define FETCH_TX_SATOSHIS_WORDS_INFO \
"transaction\n" \
"{\n" \
"    hash 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            previous_output 0000000000000000000000000000000000000000000000000000000000000000:4294967295\n" \
"            script \"[ 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73 ]\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address 1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa\n" \
"            script \"[ 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f ] checksig\"\n" \
"            value 5000000000\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

#define FETCH_TX_SECOND_TX_HASH \
"0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098"
#define FETCH_TX_SECOND_TX_NATIVE \
"01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff0704ffff001d0104ffffffff0100f2052a0100000043410496b538e853519c726a2c91e61ec11600ae1390813a627c66fb8be7947be63c52da7589379515d4e0a604f8141781e62294721166bf621e73a82cbf2342c858eeac00000000"
#define FETCH_TX_SECOND_TX_INFO \
"transaction\n" \
"{\n" \
"    hash 0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            previous_output 0000000000000000000000000000000000000000000000000000000000000000:4294967295\n" \
"            script \"[ 04ffff001d0104 ]\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address 12c6DSiU4Rq3P4ZxziKxzrL5LmMBrzjrJX\n" \
"            script \"[ 0496b538e853519c726a2c91e61ec11600ae1390813a627c66fb8be7947be63c52da7589379515d4e0a604f8141781e62294721166bf621e73a82cbf2342c858ee ] checksig\"\n" \
"            value 5000000000\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_satoshis_words_tx_native__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_tx);
    command.set_format_option({ "native" });
    command.set_hashs_argument({ { BX_SATOSHIS_WORDS_TX_HASH } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SATOSHIS_WORDS_TX_BASE16 "\n");
}

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_satoshis_words_tx_xml__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_tx);
    command.set_format_option({ "xml" });
    command.set_hashs_argument({ { BX_SATOSHIS_WORDS_TX_HASH } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_SATOSHIS_WORDS_XML);
}

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_satoshis_words_tx_twice_info__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_tx);
    command.set_format_option({ "info" });
    command.set_hashs_argument({ { BX_SATOSHIS_WORDS_TX_HASH }, { BX_SATOSHIS_WORDS_TX_HASH } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_SATOSHIS_WORDS_INFO FETCH_TX_SATOSHIS_WORDS_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_second_tx_native__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_tx);
    command.set_format_option({ "native" });
    command.set_hashs_argument({ { FETCH_TX_SECOND_TX_HASH } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_SECOND_TX_NATIVE "\n");
}

BOOST_AUTO_TEST_CASE(fetch_tx__invoke__mainnet_second_tx_info__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_tx);
    command.set_format_option({ "info" });
    command.set_hashs_argument({ { FETCH_TX_SECOND_TX_HASH } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(FETCH_TX_SECOND_TX_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()