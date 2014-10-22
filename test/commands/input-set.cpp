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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(input_set__invoke)

#define INPUT_SIGNATURE_SCRIPT_A "[ 3044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd ] [ 03c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0 ]"
#define INPUT_SET_TX_IN_A "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"
#define INPUT_SET_TX_OUT_A "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000069463044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd2103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

BOOST_AUTO_TEST_CASE(input_set__invoke__single_input__okay_output)
{
    BX_DECLARE_COMMAND(input_set);
    command.set_transaction_argument({ INPUT_SET_TX_IN_A });
    command.set_signature_script_argument({ INPUT_SIGNATURE_SCRIPT_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(INPUT_SET_TX_OUT_A "\n");
}

BOOST_AUTO_TEST_CASE(input_set__invoke__single_input_invalid_index__failure_error)
{
    BX_DECLARE_COMMAND(input_set);
    command.set_index_option(1);
    command.set_transaction_argument({ INPUT_SET_TX_IN_A });
    command.set_signature_script_argument({ INPUT_SIGNATURE_SCRIPT_A });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_INPUT_SET_INDEX_OUT_OF_RANGE "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()