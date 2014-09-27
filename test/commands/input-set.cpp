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

BOOST_AUTO_TEST_SUITE(input_set__invoke)

#define INPUT_SIGNATURE_SCRIPT_A "[ 3045022100d303bbe206ef6bc5c1033044a36145aac642600dbe9e0f1b725cd9f16c719bfe022045c57877f5242e0311c705713cffec6eb372949970b066988756bca30b7c6755 ] [ 03c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0 ]"
#define INPUT_SET_TX_IN_A "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970000000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"
#define INPUT_SET_TX_OUT_A "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee097000000006a473045022100d303bbe206ef6bc5c1033044a36145aac642600dbe9e0f1b725cd9f16c719bfe022045c57877f5242e0311c705713cffec6eb372949970b066988756bca30b7c67552103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

BOOST_AUTO_TEST_CASE(input_set__invoke__always__failure_error)
{
    BX_DECLARE_COMMAND(input_set);
    command.set_index_option(0);
    command.set_transaction_argument({ INPUT_SET_TX_IN_A });
    command.set_signature_and_pubkey_script_argument({ INPUT_SIGNATURE_SCRIPT_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(INPUT_SET_TX_OUT_A "\n");
}

BOOST_AUTO_TEST_SUITE_END()