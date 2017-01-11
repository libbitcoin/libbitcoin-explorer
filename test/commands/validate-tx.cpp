/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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

#define VALIDATE_TX_BAD_SIGNATURE_TX_BASE16 \
"0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000069463044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd2103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

#define VALIDATE_TX_NEW_TX_BASE16 \
"0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee097010000006a473044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd012103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

BOOST_AUTO_TEST_CASE(validate_tx__invoke__mainnet_satoshis_words__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(validate_tx);
    command.set_transaction_argument({ BX_SATOSHIS_WORDS_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(coinbase_transaction) + "\n");
}

BOOST_AUTO_TEST_CASE(validate_tx__invoke__bad_signature_tx__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(validate_tx);
    command.set_transaction_argument({ VALIDATE_TX_BAD_SIGNATURE_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(invalid_script) + "\n");
}

BOOST_AUTO_TEST_CASE(validate_tx__invoke__new_tx__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(validate_tx);
    command.set_transaction_argument({ VALIDATE_TX_NEW_TX_BASE16 });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ERROR_MESSAGE(invalid_script) + "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
