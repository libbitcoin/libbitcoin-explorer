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
BOOST_AUTO_TEST_SUITE(fetch_utxo__invoke)

const auto fetch_utxo_greedy_tx_info =                                  \
    "points\n"                                                          \
    "{\n"                                                               \
    "    points\n"                                                      \
    "    {\n"                                                           \
    "        hash db9e8d8a112437a5fc620c969cc76f3683e98475737c286d62002369f0f46fe5\n" \
    "        index 0\n"                                                 \
    "    }\n"                                                           \
    "}\n"                                                               \
    "change 200010000\n";

const auto fetch_utxo_individual_tx_info =                              \
    "points\n"                                                          \
    "{\n"                                                               \
    "    points\n"                                                      \
    "    {\n"                                                           \
    "        hash 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n" \
    "        index 0\n"                                                 \
    "    }\n"                                                           \
    "}\n"                                                               \
    "change 0\n";

BOOST_AUTO_TEST_CASE(fetch_utxo__invoke__mainnet_greedy_tx_info__okay_output)
{
   BX_DECLARE_NETWORK_COMMAND(bc::explorer::commands::fetch_utxo);
   command.set_format_option({"info"});
   command.set_satoshi_argument(199990000);
   command.set_payment_address_argument({"1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"});
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT(fetch_utxo_greedy_tx_info);
}

BOOST_AUTO_TEST_CASE(fetch_utxo__invoke__mainnet_individual_tx_info__okay_output)
{
   BX_DECLARE_NETWORK_COMMAND(bc::explorer::commands::fetch_utxo);
   command.set_format_option({"info"});
   command.set_algorithm_option({ "individual" });
   command.set_satoshi_argument(4900000000);
   command.set_payment_address_argument({"1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"});
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT(fetch_utxo_individual_tx_info);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
