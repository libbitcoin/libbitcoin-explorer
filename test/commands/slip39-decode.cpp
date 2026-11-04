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
BC_AUTO_TEST_SUITE(slip39_decode__invoke)

BC_AUTO_TEST_CASE(slip39_decode__invoke__single_share__okay_output)
{
    BX_DECLARE_COMMAND(slip39_decode);
    command.set_share_argument({ "duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"identifier\":7945,\"extendable\":false,\"exponent\":0,\"group_index\":0,\"group_threshold\":1,\"group_count\":1,\"member_index\":0,\"member_threshold\":1}\n");
}

BC_AUTO_TEST_CASE(slip39_decode__invoke__member_share__okay_output)
{
    BX_DECLARE_COMMAND(slip39_decode);
    command.set_share_argument({ "shadow pistol academic acid actress prayer class unknown daughter sweater depict flip twice unkind craft early superior advocate guest smoking" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"identifier\":25653,\"extendable\":false,\"exponent\":2,\"group_index\":0,\"group_threshold\":1,\"group_count\":1,\"member_index\":0,\"member_threshold\":2}\n");
}

BC_AUTO_TEST_CASE(slip39_decode__invoke__group_share__okay_output)
{
    BX_DECLARE_COMMAND(slip39_decode);
    command.set_share_argument({ "eraser senior decision smug corner ruin rescue cubic angel tackle skin skunk program roster trash rumor slush angel flea amazing" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"identifier\":9497,\"extendable\":false,\"exponent\":0,\"group_index\":3,\"group_threshold\":2,\"group_count\":4,\"member_index\":4,\"member_threshold\":2}\n");
}

BC_AUTO_TEST_CASE(slip39_decode__invoke__extendable_share__okay_output)
{
    BX_DECLARE_COMMAND(slip39_decode);
    command.set_share_argument({ "testify swimming academic academic column loyalty smear include exotic bedroom exotic wrist lobe cover grief golden smart junior estimate learn" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"identifier\":29019,\"extendable\":true,\"exponent\":3,\"group_index\":0,\"group_threshold\":1,\"group_count\":1,\"member_index\":0,\"member_threshold\":1}\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
