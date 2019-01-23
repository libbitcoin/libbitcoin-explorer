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
BOOST_AUTO_TEST_SUITE(script_from_address__invoke)

// Vectors.
#define BX_SCRIPT_FROM_ADDRESS_ADDRESS1 "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz"
#define BX_SCRIPT_FROM_ADDRESS_ADDRESS2 "36rNbEV2yvhWxZzb61sYJ6pPcdqsQY4KrA"
#define BX_SCRIPT_FROM_ADDRESS_ADDRESS3 "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"
#define BX_SCRIPT_FROM_ADDRESS_TESTNET_ADDRESS1 "n3GNqMveyvaPvUbH469vDRadqpJMPc84JA"

// Expectations.
#define BX_SCRIPT_FROM_ADDRESS_SCRIPT1 "76a914168f67cd3f1cb6852517024bc1a27c0d3f052a7788ac\n"
#define BX_SCRIPT_FROM_ADDRESS_SCRIPT2 "a914389d9fe3bb47aaae137c2fc2824d2a7ff846692e87\n"
#define BX_SCRIPT_FROM_ADDRESS_SCRIPT3 "76a91462e907b15cbf27d5425399ebf6f0fb50ebb88f1888ac\n"
#define BX_SCRIPT_FROM_ADDRESS_TESTNET_SCRIPT1 "76a914ee9103399bfb42a091a7b537bed4a8552e9611ca88ac\n"

BOOST_AUTO_TEST_CASE(script_from_address__invoke__address1__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::script_from_address);
    command.set_payment_address_argument({ BX_SCRIPT_FROM_ADDRESS_ADDRESS1 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SCRIPT_FROM_ADDRESS_SCRIPT1);
}

BOOST_AUTO_TEST_CASE(script_from_address__invoke__address2__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::script_from_address);
    command.set_payment_address_argument({ BX_SCRIPT_FROM_ADDRESS_ADDRESS2 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SCRIPT_FROM_ADDRESS_SCRIPT2);
}

BOOST_AUTO_TEST_CASE(script_from_address__invoke__address3__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::script_from_address);
    command.set_payment_address_argument({ BX_SCRIPT_FROM_ADDRESS_ADDRESS3 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SCRIPT_FROM_ADDRESS_SCRIPT3);
}

BOOST_AUTO_TEST_CASE(script_from_address__invoke__testnet_address1__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::script_from_address);
    command.set_payment_address_argument({ BX_SCRIPT_FROM_ADDRESS_TESTNET_ADDRESS1 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SCRIPT_FROM_ADDRESS_TESTNET_SCRIPT1);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
