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
BOOST_AUTO_TEST_SUITE(validate_tx__invoke)

#define VALIDATE_TX_RANDOM_TX_BASE16 \
"010000000158095935ef7f3b19dabcf3336b381ca446658f0b92d262df77d3ea75acd7dd5c000000006b4830450221008086b620eb1c494eac150ee1445362ad91fc9e42550cbb93b5bedf1e0ee984d702203797575a070791c64ba8ae7dd8f2606880c2449f2282e2c85a1b3b41bc44a7d20121035b93c629a876e2540be34a10d41a44e18db1ccffe537c51d08daacf56becabdeffffffff01706f9800000000001976a914c3a78ab9df71ad655cdd195c55585209151f4a2b88ac00000000"

#define VALIDATE_TX_BAD_SIGNATURE_TX_BASE16 \
"0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000069463044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd2103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

#define VALIDATE_TX_NEW_TX_BASE16 \
"0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee097010000006a473044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd012103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"


BOOST_AUTO_TEST_CASE(validate_tx__invoke__mainnet_satoshis_words__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(validate_tx);
    command.set_transaction_argument({ BX_SATOSHIS_WORDS_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MEMPOOL_COINBASE_TX_MESSAGE "\n");
}

BOOST_AUTO_TEST_CASE(validate_tx__invoke__mainnet_random_tx__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(validate_tx);
    command.set_transaction_argument({ VALIDATE_TX_RANDOM_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MATCHING_PREVIOUS_OBJECT_MESSAGE "\n");
}

BOOST_AUTO_TEST_CASE(validate_tx__invoke__bad_signature_tx__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(validate_tx);
    command.set_transaction_argument({ VALIDATE_TX_BAD_SIGNATURE_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_VALIDATION_OF_INPUTS_FAILED "\n");
}

BOOST_AUTO_TEST_CASE(validate_tx__invoke__new_tx__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(validate_tx);
    command.set_transaction_argument({ VALIDATE_TX_NEW_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_VALIDATION_OF_INPUTS_FAILED "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()