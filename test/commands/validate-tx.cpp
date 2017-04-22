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
BOOST_AUTO_TEST_SUITE(validate_tx__invoke)

#define VALIDATE_TX_BAD_SIGNATURE_TX_BASE16 \
"0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000069463044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd2103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

#define VALIDATE_TX_NEW_TX_BASE16 \
"0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee097010000006a473044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd012103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

#define VALIDATE_TX_ISSUE_477 \
"0100000001833d56a22cd88ef7a17d51d30b169a86aa4138f60867a6e21fc88a7b546b5d64010000006a4730440220688fb2aef767f21127b375d50d0ab8f7a1abaecad08e7c4987f7305c90e5a02502203282909b7863149bf4c92589764df80744afb509b949c06bfbeb28864277d88d0121025334b571c11e22967452f195509260f6a6dd10357fc4ad76b1c0aa5981ac254effffffff030000000000000000246a22414243444546917ce6520f0740cd2c373bd506415777bd23e8680123456789abcdef10270000000000001976a914ce5b06176d2572d4fb985747f197c389b8ac64e888ac30750000000000001976a9143c6602137d7f9a68a96aff2d3cf37bbdeeb95b7d88ac00000000"

BOOST_AUTO_TEST_CASE(validate_tx__invoke__mainnet_satoshis_words__failure_coinbase_transaction)
{
    BX_DECLARE_CLIENT_COMMAND(validate_tx);
    command.set_transaction_argument({ BX_SATOSHIS_WORDS_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(coinbase_transaction) + "\n");
}

BOOST_AUTO_TEST_CASE(validate_tx__invoke__bad_signature_tx__failure_missing_previous_output)
{
    BX_DECLARE_CLIENT_COMMAND(validate_tx);
    command.set_transaction_argument({ VALIDATE_TX_BAD_SIGNATURE_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));

    // TODO: With store commit and robust error reporting this now returns
    // error::missing_previous_output. Need to determine if this is correct.
    ////BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(invalid_script) + "\n");
    BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(missing_previous_output) + "\n");
}

BOOST_AUTO_TEST_CASE(validate_tx__invoke__new_tx__failure_missing_previous_output)
{
    BX_DECLARE_CLIENT_COMMAND(validate_tx);
    command.set_transaction_argument({ VALIDATE_TX_NEW_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));

    // TODO: With store commit and robust error reporting this now returns
    // error::missing_previous_output. Need to determine if this is correct.
    ////BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(invalid_script) + "\n");
    BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(missing_previous_output) + "\n");
}

BOOST_AUTO_TEST_CASE(validate_tx__invoke__issue_477__failure_op_equal_verify2)
{
    BX_DECLARE_CLIENT_COMMAND(validate_tx);
    command.set_transaction_argument({ VALIDATE_TX_ISSUE_477 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(op_equal_verify2) + "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
