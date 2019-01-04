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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(input_validate__invoke)

// The public key of the signer, who is also the owner of the output, derived from INPUT_SIGN_PRIVATE_KEY_A.
#define INPUT_VALIDATE_PUBLIC_KEY_A "03c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0"

// This is the signature INPUT_SIGN_SIGNATURE_A for the input signed by INPUT_SIGN_PRIVATE_KEY_A.
#define INPUT_VALIDATE_ENDORSEMENT_A "3044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd01"

// This is the previous output which was signed as the new tx input.
#define INPUT_VALIDATE_PREVOUT_SCRIPT_A "dup hash160 [88350574280395ad2c3e2ee20e322073d94e5e40] equalverify checksig"

// This is the new transaction which includes the previous output reference (as input) and the new outputs, all of which which were signed.
#define INPUT_VALIDATE_TX_A "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee097010000006a473044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd012103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

// One input no output.
#define INPUT_VALIDATE_TX_B "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970000000000ffffffff0000000000"

BOOST_AUTO_TEST_CASE(input_validate__invoke__single_input_single_output__okay_output)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_PUBLIC_KEY_A });
    command.set_endorsement_argument({ INPUT_VALIDATE_ENDORSEMENT_A });
    command.set_contract_argument({ INPUT_VALIDATE_PREVOUT_SCRIPT_A });
    command.set_transaction_argument({ INPUT_VALIDATE_TX_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_INPUT_VALIDATE_INDEX_VALID_ENDORSEMENT "\n");
}

BOOST_AUTO_TEST_CASE(input_validate__invoke__invalid_index__failure_error)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_index_option(42);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_PUBLIC_KEY_A });
    command.set_endorsement_argument({ INPUT_VALIDATE_ENDORSEMENT_A });
    command.set_contract_argument({ INPUT_VALIDATE_PREVOUT_SCRIPT_A });
    command.set_transaction_argument({ INPUT_VALIDATE_TX_A });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_INPUT_VALIDATE_INDEX_OUT_OF_RANGE "\n");
}

BOOST_AUTO_TEST_CASE(input_validate__invoke__single_input_no_output__invalid_output)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_PUBLIC_KEY_A });
    command.set_endorsement_argument({ INPUT_VALIDATE_ENDORSEMENT_A });
    command.set_contract_argument({ INPUT_VALIDATE_PREVOUT_SCRIPT_A });
    command.set_transaction_argument({ INPUT_VALIDATE_TX_B });
    BX_REQUIRE_INVALID(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_INPUT_VALIDATE_INDEX_INVALID_ENDORSEMENT "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
