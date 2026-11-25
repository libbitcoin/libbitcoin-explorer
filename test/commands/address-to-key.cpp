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
BC_AUTO_TEST_SUITE(address_to_key__invoke)

// Vectors.
#define BX_ADDRESS_TO_KEY_ADDRESS1 "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz"
#define BX_ADDRESS_TO_KEY_ADDRESS2 "36rNbEV2yvhWxZzb61sYJ6pPcdqsQY4KrA"
#define BX_ADDRESS_TO_KEY_ADDRESS3 "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"
#define BX_ADDRESS_TO_KEY_TESTNET_ADDRESS1 "n3GNqMveyvaPvUbH469vDRadqpJMPc84JA"

// Expectations.
#define BX_ADDRESS_TO_KEY_KEY1 "f8ad09745f9b3bcad7c7ffbfc112e7164df678aae381f3a3ead3a35013bee0a0\n"
#define BX_ADDRESS_TO_KEY_KEY2 "7304167ecb5078bf016d8ce883173809fecd712772e2e06563a9b3d65e1bec52\n"
#define BX_ADDRESS_TO_KEY_KEY3 "8b01df4e368ea28f8dc0423bcf7a4923e3a12d307c875e47a0cfbf90b5c39161\n"
#define BX_ADDRESS_TO_KEY_TESTNET_KEY1 "a7ecc21d4b41234b3eff65a0bac69c54de166c1e1ccee3ae730637c4346cbf1a\n"

BC_AUTO_TEST_CASE(address_to_key__invoke__address1__okay_output)
{
    BX_DECLARE_COMMAND(bc::explorer::commands::address_to_key);
    command.set_payment_address_argument({ BX_ADDRESS_TO_KEY_ADDRESS1 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_TO_KEY_KEY1);
}

BC_AUTO_TEST_CASE(address_to_key__invoke__address2__okay_output)
{
    BX_DECLARE_COMMAND(bc::explorer::commands::address_to_key);
    command.set_wallet_pay_to_script_hash_version_setting(5);
    command.set_payment_address_argument({ BX_ADDRESS_TO_KEY_ADDRESS2 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_TO_KEY_KEY2);
}

BC_AUTO_TEST_CASE(address_to_key__invoke__address3__okay_output)
{
    BX_DECLARE_COMMAND(bc::explorer::commands::address_to_key);
    command.set_payment_address_argument({ BX_ADDRESS_TO_KEY_ADDRESS3 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_TO_KEY_KEY3);
}

BC_AUTO_TEST_CASE(address_to_key__invoke__testnet_address1__okay_output)
{
    BX_DECLARE_COMMAND(bc::explorer::commands::address_to_key);
    command.set_wallet_pay_to_public_key_hash_version_setting(111);
    command.set_payment_address_argument({ BX_ADDRESS_TO_KEY_TESTNET_ADDRESS1 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_TO_KEY_TESTNET_KEY1);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
