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
BOOST_AUTO_TEST_SUITE(address_to_key__invoke)

// Vectors.
#define BX_ADDRESS_TO_KEY_ADDRESS1 "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz"
#define BX_ADDRESS_TO_KEY_ADDRESS2 "36rNbEV2yvhWxZzb61sYJ6pPcdqsQY4KrA"
#define BX_ADDRESS_TO_KEY_ADDRESS3 "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"
#define BX_ADDRESS_TO_KEY_TESTNET_ADDRESS1 "n3GNqMveyvaPvUbH469vDRadqpJMPc84JA"

// Expectations.
#define BX_ADDRESS_TO_KEY_KEY1 "a0e0be1350a3d3eaa3f381e3aa78f64d16e712c1bfffc7d7ca3b9b5f7409adf8\n"
#define BX_ADDRESS_TO_KEY_KEY2 "52ec1b5ed6b3a96365e0e2722771cdfe09381783e88c6d01bf7850cb7e160473\n"
#define BX_ADDRESS_TO_KEY_KEY3 "6191c3b590bfcfa0475e877c302da1e323497acf3b42c08d8fa28e364edf018b\n"
#define BX_ADDRESS_TO_KEY_TESTNET_KEY1 "1abf6c34c4370673aee3ce1c1e6c16de549cc6baa065ff3e4b23414b1dc2eca7\n"

BOOST_AUTO_TEST_CASE(address_to_key__invoke__address1__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::address_to_key);
    command.set_payment_address_argument({ BX_ADDRESS_TO_KEY_ADDRESS1 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_TO_KEY_KEY1);
}

BOOST_AUTO_TEST_CASE(address_to_key__invoke__address2__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::address_to_key);
    command.set_payment_address_argument({ BX_ADDRESS_TO_KEY_ADDRESS2 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_TO_KEY_KEY2);
}

BOOST_AUTO_TEST_CASE(address_to_key__invoke__address3__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::address_to_key);
    command.set_payment_address_argument({ BX_ADDRESS_TO_KEY_ADDRESS3 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_TO_KEY_KEY3);
}

BOOST_AUTO_TEST_CASE(address_to_key__invoke__testnet_address1__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::address_to_key);
    command.set_payment_address_argument({ BX_ADDRESS_TO_KEY_TESTNET_ADDRESS1 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_TO_KEY_TESTNET_KEY1);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
