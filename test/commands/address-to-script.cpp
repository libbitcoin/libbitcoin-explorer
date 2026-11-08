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
BC_AUTO_TEST_SUITE(address_to_script__invoke)

BC_AUTO_TEST_CASE(address_to_script__invoke__pay_key_hash__okay_output)
{
    BX_DECLARE_COMMAND(address_to_script);
    command.set_wallet_pay_to_public_key_hash_version_setting(0);
    command.set_wallet_pay_to_script_hash_version_setting(5);
    command.set_payment_address_argument({ "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("dup hash160 [62e907b15cbf27d5425399ebf6f0fb50ebb88f18] equalverify checksig\n");
}

BC_AUTO_TEST_CASE(address_to_script__invoke__pay_script_hash__okay_output)
{
    BX_DECLARE_COMMAND(address_to_script);
    command.set_wallet_pay_to_public_key_hash_version_setting(0);
    command.set_wallet_pay_to_script_hash_version_setting(5);
    command.set_payment_address_argument({ "36rNbEV2yvhWxZzb61sYJ6pPcdqsQY4KrA" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("hash160 [389d9fe3bb47aaae137c2fc2824d2a7ff846692e] equal\n");
}

BC_AUTO_TEST_CASE(address_to_script__invoke__testnet_pay_key_hash__okay_output)
{
    BX_DECLARE_COMMAND(address_to_script);
    command.set_wallet_pay_to_public_key_hash_version_setting(111);
    command.set_wallet_pay_to_script_hash_version_setting(196);
    command.set_payment_address_argument({ "n3GNqMveyvaPvUbH469vDRadqpJMPc84JA" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("dup hash160 [ee9103399bfb42a091a7b537bed4a8552e9611ca] equalverify checksig\n");
}

BC_AUTO_TEST_CASE(address_to_script__invoke__unconfigured_version__failure_error)
{
    BX_DECLARE_COMMAND(address_to_script);
    command.set_wallet_pay_to_public_key_hash_version_setting(0);
    command.set_wallet_pay_to_script_hash_version_setting(5);
    command.set_payment_address_argument({ "n3GNqMveyvaPvUbH469vDRadqpJMPc84JA" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ADDRESS_TO_SCRIPT_INVALID_VERSION "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
