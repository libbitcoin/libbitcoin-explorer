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
BC_AUTO_TEST_SUITE(witness_to_script__invoke)

BC_AUTO_TEST_CASE(witness_to_script__invoke__pay_witness_key_hash__okay_output)
{
    BX_DECLARE_COMMAND(witness_to_script);
    command.set_witness_address_argument({ "bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("zero [751e76e8199196d454941c45d1b3a323f1433bd6]\n");
}

BC_AUTO_TEST_CASE(witness_to_script__invoke__pay_witness_script_hash__okay_output)
{
    BX_DECLARE_COMMAND(witness_to_script);
    command.set_witness_address_argument({ "tb1qrp33g0q5c5txsp9arysrx4k6zdkfs4nce4xj0gdcccefvpysxf3q0sl5k7" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("zero [1863143c14c5166804bd19203356da136c985678cd4d27a1b8c6329604903262]\n");
}

BC_AUTO_TEST_CASE(witness_to_script__invoke__taproot__okay_output)
{
    BX_DECLARE_COMMAND(witness_to_script);
    command.set_witness_address_argument({ "bc1p0xlxvlhemja6c4dqv22uapctqupfhlxm9h8z3k2e72q4k9hcz7vqzk5jj0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1 [79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798]\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
