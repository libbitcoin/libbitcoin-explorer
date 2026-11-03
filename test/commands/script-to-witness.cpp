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
BC_AUTO_TEST_SUITE(script_to_witness__invoke)

// The witness program is the sha256 of the serialized output script.
#define SCRIPT_TO_WITNESS_SCRIPT "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig"

BC_AUTO_TEST_CASE(script_to_witness__invoke__mainnet__okay_output)
{
    BX_DECLARE_COMMAND(script_to_witness);
    command.set_prefix_argument({ "bc" });
    command.set_script_argument({ SCRIPT_TO_WITNESS_SCRIPT });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bc1q3039wrwehsr9av7suufjcnnmue8umptqhey6dntmwthrfyrs7xzqmsl4ur\n");
}

BC_AUTO_TEST_CASE(script_to_witness__invoke__testnet__okay_output)
{
    BX_DECLARE_COMMAND(script_to_witness);
    command.set_prefix_argument({ "tb" });
    command.set_script_argument({ SCRIPT_TO_WITNESS_SCRIPT });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("tb1q3039wrwehsr9av7suufjcnnmue8umptqhey6dntmwthrfyrs7xzqvcf6xv\n");
}

BC_AUTO_TEST_CASE(script_to_witness__invoke__default_prefix__failure_error)
{
    BX_DECLARE_COMMAND(script_to_witness);
    command.set_script_argument({ SCRIPT_TO_WITNESS_SCRIPT });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SCRIPT_TO_WITNESS_INVALID_PREFIX "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
