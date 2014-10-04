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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(tx_decode__invoke)

// Vector: sx.dyne.org/offlinetx.html

#define TX_DECODE_TX_A_NATIVE \
"0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

#define TX_DECODE_TX_A_INFO \
"transaction\n" \
"{\n" \
"    hash 39d2caaf112f21364be00c5d0b14e3763468934e586e416bf74647a1906b18e0\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            previous_output 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1\n" \
"            script \"\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe\n" \
"            script \"dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify checksig\"\n" \
"            value 90000\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

/*
#define TX_DECODE_TX_A_JSON \
"{\n" \
"    \"transaction\": {\n" \
"        \"hash\": \"39d2caaf112f21364be00c5d0b14e3763468934e586e416bf74647a1906b18e0\",\n" \
"        \"inputs\": {\n" \
"            \"input\": {\n" \
"                \"previous_output\": \"97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1\",\n" \
"                \"script\": \"\",\n" \
"                \"sequence\": \"4294967295\"\n" \
"            }\n" \
"        },\n" \
"        \"lock_time\": \"0\",\n" \
"        \"outputs\": {\n" \
"            \"output\": {\n" \
"                \"address\": \"13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe\",\n" \
"                \"script\": \"dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify checksig\",\n" \
"                \"value\": \"90000\"\n" \
"            }\n" \
"        },\n" \
"        \"version\": \"1\"\n" \
"    }\n" \
"}\n"
*/

#define TX_DECODE_TX_A_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<transaction><hash>39d2caaf112f21364be00c5d0b14e3763468934e586e416bf74647a1906b18e0</hash><inputs><input><previous_output>97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1</previous_output><script/><sequence>4294967295</sequence></input></inputs><lock_time>0</lock_time><outputs><output><address>13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe</address><script>dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify checksig</script><value>90000</value></output></outputs><version>1</version></transaction>"

#define TX_DECODE_TX_B_NATIVE \
"0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000069463044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202204fcc407ce9b6f719ee7d009aeb8d8d21423f400a5b871394ca32e00c26b348dd2103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"
#define TX_DECODE_TX_B_INFO \
"transaction\n" \
"{\n" \
"    hash 4d6e0bb598a96255800d288fd6d70d65e9c7da8a6c69ba8ed74ade42799f801f\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            address 1DRCR5Gvg18FNo8HUPH1u5bfd9b5XfnJDj\n" \
"            previous_output 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1\n" \
"            script \"[ 3044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202204fcc407ce9b6f719ee7d009aeb8d8d21423f400a5b871394ca32e00c26b348dd ] [ 03c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0 ]\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe\n" \
"            script \"dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify checksig\"\n" \
"            value 90000\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

BOOST_AUTO_TEST_CASE(tx_decode__invoke__tx_A_info__okay_output)
{
    // Defaults are not established by the library, so 'format' is set explicitly here.
    BX_DECLARE_COMMAND(tx_decode);
    command.set_format_option({ "info" });
    command.set_transactions_argument({ { TX_DECODE_TX_A_NATIVE } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_DECODE_TX_A_INFO);
}

// JSON encoding varies subtly by boost or platform, so this is disabled.
//BOOST_AUTO_TEST_CASE(tx_decode__invoke__tx_A_json__okay_output)
//{
//    BX_DECLARE_COMMAND(tx_decode);
//    command.set_format_option({ "json" });
//    command.set_transactions_argument({ { TX_DECODE_TX_A_NATIVE } });
//    BX_REQUIRE_OKAY(command.invoke(output, error));
//    BX_REQUIRE_OUTPUT(TX_DECODE_TX_A_JSON);
//}

BOOST_AUTO_TEST_CASE(tx_decode__invoke__tx_A_xml__okay_output)
{
    BX_DECLARE_COMMAND(tx_decode);
    command.set_format_option({ "xml" });
    command.set_transactions_argument({ { TX_DECODE_TX_A_NATIVE } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_DECODE_TX_A_XML);
}

BOOST_AUTO_TEST_CASE(tx_decode__invoke__two_tx_A_native__okay_output)
{
    BX_DECLARE_COMMAND(tx_decode);
    command.set_format_option({ "native" });
    command.set_transactions_argument({ { TX_DECODE_TX_A_NATIVE }, { TX_DECODE_TX_A_NATIVE } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_DECODE_TX_A_NATIVE "\n" TX_DECODE_TX_A_NATIVE "\n");
}

BOOST_AUTO_TEST_CASE(tx_decode__invoke__tx_B__okay_output)
{
    BX_DECLARE_COMMAND(tx_decode);
    command.set_format_option({ "info" });
    command.set_transactions_argument({ { TX_DECODE_TX_B_NATIVE } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_DECODE_TX_B_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()