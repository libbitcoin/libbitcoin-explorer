/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(tx_decode__invoke)

#define TX_DECODE_EXAMPLE1 \
"transaction\n" \
"{\n" \
"    hash f9be6abf60342de5606421c7deaaf2d3f7133490db5242e8507e05926b16d090\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            previous_output\n" \
"            {\n" \
"                hash 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3\n" \
"                index 0\n" \
"            }\n" \
"            script \"\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address_hash 58b7a60f11a904feef35a639b6048de8dd4d9f1c\n" \
"            script \"dup hash160 [58b7a60f11a904feef35a639b6048de8dd4d9f1c] equalverify checksig\"\n" \
"            value 45000\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

#define TX_DECODE_EXAMPLE2 \
"transaction\n" \
"{\n" \
"    hash 4a013715c2ef8ddeae2792eea4751565acd1ad5ed27542d45f2ebe571f4899e9\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            previous_output\n" \
"            {\n" \
"                hash 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3\n" \
"                index 1\n" \
"            }\n" \
"            script \"\"\n" \
"            sequence 7\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            script \"return [14576f496f20b0befe21f39f765e81543ebd1790ec4a03d1b5a1c2e912749d90d0fd7b16322749e301a2b0dbfe278509011564590412b277]\"\n" \
"            stealth\n" \
"            {\n" \
"                prefix 2927803294\n" \
"                ephemeral_public_key 0214576f496f20b0befe21f39f765e81543ebd1790ec4a03d1b5a1c2e912749d90\n" \
"            }\n" \
"            value 0\n" \
"        }\n" \
"        output\n" \
"        {\n" \
"            address_hash cc04492c12d0ddeb4cf88cfccb0d6d78d0fcd39d\n" \
"            script \"dup hash160 [cc04492c12d0ddeb4cf88cfccb0d6d78d0fcd39d] equalverify checksig\"\n" \
"            value 42\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

#define TX_DECODE_EXAMPLE3 \
"transaction\n" \
"{\n" \
"    hash bfe73280b111a7dae1714b1efe869c0d0c854dd9d1c3ba51fa439e7fb4d0e63c\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            previous_output\n" \
"            {\n" \
"                hash 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3\n" \
"                index 1\n" \
"            }\n" \
"            script \"\"\n" \
"            sequence 7\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address_hash 18c0bd8d1818f1bf99cb1df2269c645318ef7b73\n" \
"            script \"dup hash160 [18c0bd8d1818f1bf99cb1df2269c645318ef7b73] equalverify checksig\"\n" \
"            value 500\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

#define TX_DECODE_EXAMPLE4 \
"transaction\n" \
"{\n" \
"    hash 37c9c4ee0e84c7c7924f74d92cf0779ec6e8fc4c57ebab2593562d52c61c5eb8\n" \
"    inputs\n" \
"    {\n" \
"        input\n" \
"        {\n" \
"            address_hash c564c740c6900b93afc9f1bdaef0a9d466adf6ee\n" \
"            previous_output\n" \
"            {\n" \
"                hash 7c3e880e7c93a7b01506188c36a239f70b561dfa622d0aa0d8f3b7403c94017d\n" \
"                index 0\n" \
"            }\n" \
"            script \"[30450221008f66d188c664a8088893ea4ddd9689024ea5593877753ecc1e9051ed58c15168022037109f0d06e6068b7447966f751de8474641ad2b15ec37f4a9d159b02af6817401] [03e208f5403383c77d5832a268c9f71480f6e7bfbdfa44904becacfad66163ea31]\"\n" \
"            sequence 4294967295\n" \
"        }\n" \
"    }\n" \
"    lock_time 0\n" \
"    outputs\n" \
"    {\n" \
"        output\n" \
"        {\n" \
"            address_hash 58b7a60f11a904feef35a639b6048de8dd4d9f1c\n" \
"            script \"dup hash160 [58b7a60f11a904feef35a639b6048de8dd4d9f1c] equalverify checksig\"\n" \
"            value 45000\n" \
"        }\n" \
"    }\n" \
"    version 1\n" \
"}\n"

BOOST_AUTO_TEST_CASE(tx_decode__invoke__example_1__expected_output)
{
    BX_DECLARE_COMMAND(tx_decode);
    command.set_format_option({ "info" });
    command.set_transaction_argument({ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970000000000ffffffff01c8af0000000000001976a91458b7a60f11a904feef35a639b6048de8dd4d9f1c88ac00000000" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_DECODE_EXAMPLE1);
}

BOOST_AUTO_TEST_CASE(tx_decode__invoke__example_2__expected_output)
{
    BX_DECLARE_COMMAND(tx_decode);
    command.set_format_option({ "info" });
    command.set_transaction_argument({ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000070000000200000000000000003a6a3814576f496f20b0befe21f39f765e81543ebd1790ec4a03d1b5a1c2e912749d90d0fd7b16322749e301a2b0dbfe278509011564590412b2772a000000000000001976a914cc04492c12d0ddeb4cf88cfccb0d6d78d0fcd39d88ac00000000" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_DECODE_EXAMPLE2);
}

BOOST_AUTO_TEST_CASE(tx_decode__invoke__example_3__expected_output)
{
    BX_DECLARE_COMMAND(tx_decode);
    command.set_format_option({ "info" });
    command.set_transaction_argument({ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee09701000000000700000001f4010000000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_DECODE_EXAMPLE3);
}

BOOST_AUTO_TEST_CASE(tx_decode__invoke__example_4__expected_output)
{
    BX_DECLARE_COMMAND(tx_decode);
    command.set_format_option({ "info" });
    command.set_transaction_argument({ "01000000017d01943c40b7f3d8a00a2d62fa1d560bf739a2368c180615b0a7937c0e883e7c000000006b4830450221008f66d188c664a8088893ea4ddd9689024ea5593877753ecc1e9051ed58c15168022037109f0d06e6068b7447966f751de8474641ad2b15ec37f4a9d159b02af68174012103e208f5403383c77d5832a268c9f71480f6e7bfbdfa44904becacfad66163ea31ffffffff01c8af0000000000001976a91458b7a60f11a904feef35a639b6048de8dd4d9f1c88ac00000000" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_DECODE_EXAMPLE4);
}

////BOOST_AUTO_TEST_CASE(tx_decode__invoke__issue_477__expected_output)
////{
////    BX_DECLARE_COMMAND(tx_decode);
////    command.set_format_option({ "info" });
////    command.set_transaction_argument({ "0100000001833d56a22cd88ef7a17d51d30b169a86aa4138f60867a6e21fc88a7b546b5d64010000006a4730440220688fb2aef767f21127b375d50d0ab8f7a1abaecad08e7c4987f7305c90e5a02502203282909b7863149bf4c92589764df80744afb509b949c06bfbeb28864277d88d0121025334b571c11e22967452f195509260f6a6dd10357fc4ad76b1c0aa5981ac254effffffff030000000000000000246a22414243444546917ce6520f0740cd2c373bd506415777bd23e8680123456789abcdef10270000000000001976a914ce5b06176d2572d4fb985747f197c389b8ac64e888ac30750000000000001976a9143c6602137d7f9a68a96aff2d3cf37bbdeeb95b7d88ac00000000" });
////    BX_REQUIRE_OKAY(command.invoke(output, error));
////    BX_REQUIRE_OUTPUT(TX_DECODE_EXAMPLE4);
////}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
