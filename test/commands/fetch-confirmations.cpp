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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_confirmations__invoke)

// BUGBUG: invalid server returns.

#define FETCH_CONFIRMATIONS_RANDOM_TX_BASE16 \
"010000000158095935ef7f3b19dabcf3336b381ca446658f0b92d262df77d3ea75acd7dd5c000000006b4830450221008086b620eb1c494eac150ee1445362ad91fc9e42550cbb93b5bedf1e0ee984d702203797575a070791c64ba8ae7dd8f2606880c2449f2282e2c85a1b3b41bc44a7d20121035b93c629a876e2540be34a10d41a44e18db1ccffe537c51d08daacf56becabdeffffffff01706f9800000000001976a914c3a78ab9df71ad655cdd195c55585209151f4a2b88ac00000000"

BOOST_AUTO_TEST_CASE(fetch_confirmations__invoke__mainnet_satoshis_words__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_confirmations);
    command.set_transactions_argument({ { BX_SATOSHIS_WORDS_TX_BASE16 } });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MEMPOOL_COINBASE_TX_MESSAGE "\n");
}

BOOST_AUTO_TEST_CASE(fetch_confirmations__invoke__mainnet_random_tx__failure_error)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_confirmations);
    command.set_transactions_argument({ { FETCH_CONFIRMATIONS_RANDOM_TX_BASE16 } });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MATCHING_PREVIOUS_OBJECT_MESSAGE "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()