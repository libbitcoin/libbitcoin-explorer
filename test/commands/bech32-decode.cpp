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
BC_AUTO_TEST_SUITE(bech32_decode__invoke)

BC_AUTO_TEST_CASE(bech32_decode__invoke__version_0_key_hash__okay_output)
{
    BX_DECLARE_COMMAND(bech32_decode);
    command.set_address_argument("bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"bech32\":{\"prefix\":\"bc\",\"program\":\"751e76e8199196d454941c45d1b3a323f1433bd6\",\"version\":0}}\n");
}

BC_AUTO_TEST_CASE(bech32_decode__invoke__version_1_taproot__okay_output)
{
    BX_DECLARE_COMMAND(bech32_decode);
    command.set_address_argument("bc1p0xlxvlhemja6c4dqv22uapctqupfhlxm9h8z3k2e72q4k9hcz7vqzk5jj0");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"bech32\":{\"prefix\":\"bc\",\"program\":\"79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798\",\"version\":1}}\n");
}

BC_AUTO_TEST_CASE(bech32_decode__invoke__version_16__okay_output)
{
    BX_DECLARE_COMMAND(bech32_decode);
    command.set_address_argument("bc1sw50qgdz25j");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"bech32\":{\"prefix\":\"bc\",\"program\":\"751e\",\"version\":16}}\n");
}

BC_AUTO_TEST_CASE(bech32_decode__invoke__surrounding_whitespace__okay_output)
{
    BX_DECLARE_COMMAND(bech32_decode);
    command.set_address_argument(" bc1sw50qgdz25j\n");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"bech32\":{\"prefix\":\"bc\",\"program\":\"751e\",\"version\":16}}\n");
}

BC_AUTO_TEST_CASE(bech32_decode__invoke__bad_checksum__failure_error)
{
    BX_DECLARE_COMMAND(bech32_decode);
    command.set_address_argument("bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t5");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_BECH32_DECODE_INVALID_CHECKSUM "\n");
}

BC_AUTO_TEST_CASE(bech32_decode__invoke__mixed_case__failure_error)
{
    BX_DECLARE_COMMAND(bech32_decode);
    command.set_address_argument("bc1qW508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_BECH32_DECODE_INVALID "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
