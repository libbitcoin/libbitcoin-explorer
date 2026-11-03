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
BC_AUTO_TEST_SUITE(dice_entropy__invoke)

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_52_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "0123450123450123450123450123450123450123450123450123" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6b13aad60391ef0047fecd298282a5c3\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_52_mixed_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "0120120120120120120120122334454301223012321543453201" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2e8c79225ae601708b2089ce797d8961\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_52_zeros__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "0000000000000000000000000000000000000000000000000000" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("00000000000000000000000000000000\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_102_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "012345012345012345012345012345012345012345012345012345012345012345012345012345012345012345012345012345" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1e978f00617621aa87960ee62ce47aaddfce967b2a1d06d4d814d9d65a5f4f89\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_102_mixed_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "012012012012012012012012233445543012230123215434532012012012012012012012012233445543012230123215434532" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("8ed16f02b01968e72228f3636df1e59f80eedda145230d68bf80418a49b1b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_53_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "54321054321054321054321054321054321054321054321054321" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ec8f854bdfabf47adf16673106f0f01d69\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__two_sides_128_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(2);
    command.set_rolls_argument({ "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("55555555555555555555555555555555\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__two_sides_8_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(2);
    command.set_rolls_argument({ "10000001" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("81\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__four_sides_64_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(4);
    command.set_rolls_argument({ "0123012301230123012301230123012301230123012301230123012301230123" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__eight_sides_43_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(8);
    command.set_rolls_argument({ "0123456701234567012345670123456701234567012" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0a72ee0a72ee0a72ee0a72ee0a72ee0a\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_40_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "0123456789012345678901234567890123456789" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("5ce0e9a56015fec5aadfa328ae398115\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_79_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "9876543210987654321098765432109876543210987654321098765432109876543210987654321" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("4ba55ba14148fdff9bc3da35f252dfed9fe8bfc4a9af0a63154fd72f21c70cb1\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__twelve_sides_36_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(12);
    command.set_rolls_argument({ "0123456789ab0123456789ab0123456789ab" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("04682f20e34e0189ec43a2868b130a93\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_32_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "0123456789abcdef0123456789abcdef" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0123456789abcdef0123456789abcdef\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_34_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "0123456789abcdef0123456789abcdefff" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0123456789abcdef0123456789abcdefff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_2_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "a5" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("a5\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_128_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_52_rolls_at_limit__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "5544124503014154002532533000500125104325044543122023" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_empty__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_3_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "012" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_50_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "01234501234501234501234501234501234501234501234501" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_51_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "012345012345012345012345012345012345012345012345012" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_100_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "0123450123450123450123450123450123450123450123450123450123450123450123450123450123450123450123450123" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_39_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "012345678901234567890123456789012345678" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_3_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "abc" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__eight_sides_44_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(8);
    command.set_rolls_argument({ "01234567012345670123456701234567012345670123" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__two_sides_9_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(2);
    command.set_rolls_argument({ "100000011" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_1_roll__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "f" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_130_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_COUNT "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_256_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_face_six__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "6000000000000000000000000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_letter__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "a000000000000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_uppercase__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "A0000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_52_rolls_above_limit__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "5544124503014154002532533000500125104325044543122024" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_REJECTED "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_52_fives__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "5555555555555555555555555555555555555555555555555555" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_REJECTED "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_40_nines__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "9999999999999999999999999999999999999999" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_REJECTED "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__one_side__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(1);
    command.set_rolls_argument({ "0000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_SIDES_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__seventeen_sides__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(17);
    command.set_rolls_argument({ "0000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ENTROPY_SIDES_INVALID "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
