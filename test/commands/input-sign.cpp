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

BOOST_AUTO_TEST_SUITE(input_sign__invoke)

// Vector A from sx.dyne.org/offlinetx.html
// The private key must correspond to the input for the signature to validate.
// The public key hash in the input (previous output) script is derived from 
// the private key. The input is presumed to be from the transaction referred 
// to by the tx input referenced by the index, but that cannot be validated 
// here. The signature is deterministic only when the same nonce is used. In 
// other words this signature will not match the sx example because the nonce
// was internal (not exposed) to the sx implementation.
#define INPUT_SIGN_NONCE_A "000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f"
#define INPUT_SIGN_PRIVATE_KEY_A "ce8f4b713ffdd2658900845251890f30371856be201cd1f5b3d970f793634333"
#define INPUT_SIGN_INPUT_A "dup hash160 [ 88350574280395ad2c3e2ee20e322073d94e5e40 ] equalverify checksig"
#define INPUT_SIGN_TX_A "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970000000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"
#define INPUT_SIGN_SIGNATURE_A "3045022100d303bbe206ef6bc5c1033044a36145aac642600dbe9e0f1b725cd9f16c719bfe022045c57877f5242e0311c705713cffec6eb372949970b066988756bca30b7c6755"

BOOST_AUTO_TEST_CASE(input_sign__invoke__single_input__okay_output)
{
    BX_DECLARE_COMMAND(input_sign);
    command.set_index_option(0);
    command.set_sighash_option({ "single" });
    command.set_nonce_argument({ INPUT_SIGN_NONCE_A });
    command.set_transaction_argument({ INPUT_SIGN_TX_A });
    command.set_prevout_script_argument({ INPUT_SIGN_INPUT_A });
    command.set_ec_private_key_argument({ INPUT_SIGN_PRIVATE_KEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(INPUT_SIGN_SIGNATURE_A "\n");
}

BOOST_AUTO_TEST_SUITE_END()