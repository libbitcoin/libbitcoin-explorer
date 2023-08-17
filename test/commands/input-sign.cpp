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
BOOST_AUTO_TEST_SUITE(input_sign__invoke)

// Vector A from sx.dyne.org/offlinetx.html
// The private key must correspond to the input for the signature to validate.
// The public key hash in the input (previous output) script is derived from
// the private key. The input is presumed to be from the transaction referred
// to by the tx input referenced by the index, but that cannot be validated
// here. This signature will not match the sx example because this signature is
// deterministic.
#define INPUT_SIGN_PRIVATE_KEY_A "ce8f4b713ffdd2658900845251890f30371856be201cd1f5b3d970f793634333"
#define INPUT_SIGN_PREVOUT_A "dup hash160 [88350574280395ad2c3e2ee20e322073d94e5e40] equalverify checksig"
#define INPUT_SIGN_TX_A "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"
//#define INPUT_SIGN_ENDORSEMENT_A "3044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd01"
#define INPUT_SIGN_ENDORSEMENT_A "3044022016516aabd04d3b27bec799bbadc55bad447db1e4bb663a32ed8ff6c6b7b6752602203651316e363b8c41c1b9db050690c6e5e9540ad04ded69184e710197734d3cf601"

// One input, no output.
// This is pathological case where a bitcoind bug is intentionally perpetuated.
#define INPUT_SIGN_TX_B "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970000000000ffffffff0000000000"
//#define INPUT_SIGN_ENDORSEMENT_B "3044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c2022013d279c191f296349f59ba1cb6e17ea1f0db8f80a26714ef573e887818d544af01"
#define INPUT_SIGN_ENDORSEMENT_B "304402204c8006959f65cb270f424521b34444198c2c80e7bf53b302085ef271b30eecf502202cf49e9136ded201e7268051eeb3838bb7e5763e0eb8aa5ed90d84a373aaaea301"

BOOST_AUTO_TEST_CASE(input_sign__invoke__single_input_single_output__okay_output)
{
    BX_DECLARE_COMMAND(input_sign);
    command.set_sign_type_option({ "all" });
    command.set_transaction_argument({ INPUT_SIGN_TX_A });
    command.set_contract_argument({ INPUT_SIGN_PREVOUT_A });
    command.set_ec_private_key_argument({ INPUT_SIGN_PRIVATE_KEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(INPUT_SIGN_ENDORSEMENT_A "\n");
}

BOOST_AUTO_TEST_CASE(input_sign__invoke__single_input_no_output__okay_output)
{
    BX_DECLARE_COMMAND(input_sign);
    command.set_sign_type_option({ "all" });
    command.set_transaction_argument({ INPUT_SIGN_TX_B });
    command.set_contract_argument({ INPUT_SIGN_PREVOUT_A });
    command.set_ec_private_key_argument({ INPUT_SIGN_PRIVATE_KEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(INPUT_SIGN_ENDORSEMENT_B "\n");
}

BOOST_AUTO_TEST_CASE(input_sign__invoke__invalid_index__failure_error)
{
    BX_DECLARE_COMMAND(input_sign);
    command.set_index_option(42);
    command.set_transaction_argument({ INPUT_SIGN_TX_A });
    command.set_contract_argument({ INPUT_SIGN_PREVOUT_A });
    command.set_ec_private_key_argument({ INPUT_SIGN_PRIVATE_KEY_A });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_INPUT_SIGN_INDEX_OUT_OF_RANGE "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
