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

BC_AUTO_TEST_SUITE(offline)
BC_AUTO_TEST_SUITE(input_validate__invoke)

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

// BIP143 native P2WPKH (input 1) and P2SH-P2WPKH (input 0) examples.
#define INPUT_VALIDATE_P2WPKH_TX "0100000002fff7f7881a8099afa6940d42d1e7f6362bec38171ea3edf433541db4e4ad969f0000000000eeffffffef51e1b804cc89d182d279655c3aa89e815b1b309fe287d9b2b55d57b90ec68a0100000000ffffffff02202cb206000000001976a9148280b37df378db99f66f85c95a783a76ac7a6d5988ac9093510d000000001976a9143bde42dbee7e4dbe6a21b2d50ce2f0167faa815988ac11000000"
#define INPUT_VALIDATE_P2WPKH_CODE "dup hash160 [1d0f172a0ecb48aee1be1f2687d2963ae33f71a1] equalverify checksig"
#define INPUT_VALIDATE_P2WPKH_KEY "025476c2e83188368da1ff3e292e7acafcdb3566bb0ad253f62fc70f07aeee6357"
#define INPUT_VALIDATE_P2WPKH_ENDORSEMENT "304402203609e17b84f6a7d30c80bfa610b5b4542f32a8a0d5447a12fb1366d7f01cc44a0220573a954c4518331561406f90300e8f3358f51928d43c212a8caed02de67eebee01"
#define INPUT_VALIDATE_P2SH_P2WPKH_TX "0100000001db6b1b20aa0fd7b23880be2ecbd4a98130974cf4748fb66092ac4d3ceb1a54770100000000feffffff02b8b4eb0b000000001976a914a457b684d7f0d539a46a45bbc043f35b59d0d96388ac0008af2f000000001976a914fd270b1ee6abcaea97fea7ad0402e8bd8ad6d77c88ac92040000"
#define INPUT_VALIDATE_P2SH_P2WPKH_CODE "dup hash160 [79091972186c449eb1ded22b78e40d009bdf0089] equalverify checksig"
#define INPUT_VALIDATE_P2SH_P2WPKH_KEY "03ad1d8e89212f0b92c74d23bb710c00662ad1470198ac48c43f7d6f93a2a26873"
#define INPUT_VALIDATE_P2SH_P2WPKH_ENDORSEMENT "3044022047ac8e878352d3ebbde1c94ce3a10d057c24175747116f8288e5d794d12d482f0220217f36a485cae903c713331d877c1f64677e3622ad4010726870540656fe9dcb01"

BC_AUTO_TEST_CASE(input_validate__invoke__single_input_single_output__okay_output)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_PUBLIC_KEY_A });
    command.set_endorsement_argument({ INPUT_VALIDATE_ENDORSEMENT_A });
    command.set_contract_argument({ INPUT_VALIDATE_PREVOUT_SCRIPT_A });
    command.set_transaction_argument({ INPUT_VALIDATE_TX_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_INPUT_VALIDATE_INDEX_VALID_ENDORSEMENT "\n");
}

BC_AUTO_TEST_CASE(input_validate__invoke__invalid_index__failure_error)
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

BC_AUTO_TEST_CASE(input_validate__invoke__single_input_no_output__invalid_output)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_PUBLIC_KEY_A });
    command.set_endorsement_argument({ INPUT_VALIDATE_ENDORSEMENT_A });
    command.set_contract_argument({ INPUT_VALIDATE_PREVOUT_SCRIPT_A });
    command.set_transaction_argument({ INPUT_VALIDATE_TX_B });
    BX_REQUIRE_INVALID(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_INPUT_VALIDATE_INDEX_INVALID_ENDORSEMENT "\n");
}

BC_AUTO_TEST_CASE(input_validate__invoke__segwit_p2wpkh__okay_output)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_index_option(1);
    command.set_segwit_option(true);
    command.set_value_option(600000000);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_P2WPKH_KEY });
    command.set_endorsement_argument({ INPUT_VALIDATE_P2WPKH_ENDORSEMENT });
    command.set_contract_argument({ INPUT_VALIDATE_P2WPKH_CODE });
    command.set_transaction_argument({ INPUT_VALIDATE_P2WPKH_TX });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_INPUT_VALIDATE_INDEX_VALID_ENDORSEMENT "\n");
}

BC_AUTO_TEST_CASE(input_validate__invoke__segwit_p2sh_p2wpkh__okay_output)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_index_option(0);
    command.set_segwit_option(true);
    command.set_value_option(1000000000);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_P2SH_P2WPKH_KEY });
    command.set_endorsement_argument({ INPUT_VALIDATE_P2SH_P2WPKH_ENDORSEMENT });
    command.set_contract_argument({ INPUT_VALIDATE_P2SH_P2WPKH_CODE });
    command.set_transaction_argument({ INPUT_VALIDATE_P2SH_P2WPKH_TX });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_INPUT_VALIDATE_INDEX_VALID_ENDORSEMENT "\n");
}

BC_AUTO_TEST_CASE(input_validate__invoke__segwit_p2wpkh_wrong_value__invalid_output)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_index_option(1);
    command.set_segwit_option(true);
    command.set_value_option(600000001);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_P2WPKH_KEY });
    command.set_endorsement_argument({ INPUT_VALIDATE_P2WPKH_ENDORSEMENT });
    command.set_contract_argument({ INPUT_VALIDATE_P2WPKH_CODE });
    command.set_transaction_argument({ INPUT_VALIDATE_P2WPKH_TX });
    BX_REQUIRE_INVALID(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_INPUT_VALIDATE_INDEX_INVALID_ENDORSEMENT "\n");
}

BC_AUTO_TEST_CASE(input_validate__invoke__p2wpkh_not_segwit__invalid_output)
{
    BX_DECLARE_COMMAND(input_validate);
    command.set_index_option(1);
    command.set_segwit_option(false);
    command.set_value_option(600000000);
    command.set_ec_public_key_argument({ INPUT_VALIDATE_P2WPKH_KEY });
    command.set_endorsement_argument({ INPUT_VALIDATE_P2WPKH_ENDORSEMENT });
    command.set_contract_argument({ INPUT_VALIDATE_P2WPKH_CODE });
    command.set_transaction_argument({ INPUT_VALIDATE_P2WPKH_TX });
    BX_REQUIRE_INVALID(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_INPUT_VALIDATE_INDEX_INVALID_ENDORSEMENT "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
