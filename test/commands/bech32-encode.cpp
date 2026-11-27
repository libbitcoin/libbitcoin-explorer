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
BC_AUTO_TEST_SUITE(bech32_encode__invoke)

BC_AUTO_TEST_CASE(bech32_encode__invoke__version_0_key_hash__okay_output)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_prefix_argument("bc");
    command.set_program_argument({ "751e76e8199196d454941c45d1b3a323f1433bd6" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4\n");
}

BC_AUTO_TEST_CASE(bech32_encode__invoke__version_0_script_hash_testnet__okay_output)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_prefix_argument("tb");
    command.set_program_argument({ "1863143c14c5166804bd19203356da136c985678cd4d27a1b8c6329604903262" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("tb1qrp33g0q5c5txsp9arysrx4k6zdkfs4nce4xj0gdcccefvpysxf3q0sl5k7\n");
}

BC_AUTO_TEST_CASE(bech32_encode__invoke__version_1_taproot__okay_output)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_version_option(1);
    command.set_prefix_argument("bc");
    command.set_program_argument({ "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bc1p0xlxvlhemja6c4dqv22uapctqupfhlxm9h8z3k2e72q4k9hcz7vqzk5jj0\n");
}

BC_AUTO_TEST_CASE(bech32_encode__invoke__version_16__okay_output)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_version_option(16);
    command.set_prefix_argument("bc");
    command.set_program_argument({ "751e" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bc1sw50qgdz25j\n");
}

BC_AUTO_TEST_CASE(bech32_encode__invoke__upper_case_prefix__failure_error)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_prefix_argument("BC");
    command.set_program_argument({ "751e76e8199196d454941c45d1b3a323f1433bd6" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_BECH32_ENCODE_INVALID_PREFIX "\n");
}

BC_AUTO_TEST_CASE(bech32_encode__invoke__version_17__failure_error)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_version_option(17);
    command.set_prefix_argument("bc");
    command.set_program_argument({ "751e" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_BECH32_ENCODE_INVALID_VERSION "\n");
}

BC_AUTO_TEST_CASE(bech32_encode__invoke__one_byte_program__failure_error)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_version_option(16);
    command.set_prefix_argument("bc");
    command.set_program_argument({ "75" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_BECH32_ENCODE_SHORT_PROGRAM "\n");
}

BC_AUTO_TEST_CASE(bech32_encode__invoke__41_byte_program__failure_error)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_version_option(16);
    command.set_prefix_argument("bc");
    command.set_program_argument({ "0000000000000000000000000000000000000000000000000000000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_BECH32_ENCODE_LONG_PROGRAM "\n");
}

BC_AUTO_TEST_CASE(bech32_encode__invoke__version_0_21_byte_program__failure_error)
{
    BX_DECLARE_COMMAND(bech32_encode);
    command.set_prefix_argument("bc");
    command.set_program_argument({ "751e76e8199196d454941c45d1b3a323f1433bd600" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_BECH32_ENCODE_INVALID_PROGRAM "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
