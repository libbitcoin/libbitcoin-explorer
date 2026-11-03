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

// Six-sided vectors match https://frozensecurity.com/tools/dice-entropy/
// with each roll written as its face value less one.

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_50_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "01234501234501234501234501234501234501234501234501" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("184ec4bed56eb86aacaaa224b5672f45\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_50_mixed_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "01201201201201201201201223345443012230123215434532" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("16a058b2bb69f1d15973a0c73d21b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_50_rolls_run_of_threes__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "01201201201201333333333333335443012230123215434532" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("16a058b2c4183470b20a7cd360e1b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_100_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "0123450123450123450123450123450123450123450123450101234501234501234501234501234501234501234501234501" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("39bd194e3b989d612e6ed5bf485bae121aa45fa1718ea167dd5ea224b5672f45\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_100_mixed_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "0120120120120120120120122334544301223012321543453201201201201201201201201223345443012230123215434532" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("35beb4dc84e442e9fa6a56f5ae9176214cdbadaf5a78f8a6cad3a0c73d21b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_100_rolls_run_of_threes__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "0120120120120133333333333333544301223012321543453201201201201201333333333333335443012230123215434532" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("35beb4dc9982da244aded20982951b2d87ff7eed3b148246236a7cd360e1b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_50_rolls_at_limit__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "50151151500355541523152131531524531055551333221011" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_100_rolls_at_limit__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "5152254435413114203302142411144331322225023141023514212400234342104220342501305311322445240143042211" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_50_zeros__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "00000000000000000000000000000000000000000000000000" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("00000000000000000000000000000000\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_56_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "01234501234501234501234501234501234501234501234501012345" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("114e1390db7212c9f16c79eea224b566e689\n");
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

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_39_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "012345678901234567890123456789012345678" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0949b0f6f0023313c4499050de38f34e\n");
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

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_3_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "abc" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bc\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_254_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_empty__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_3_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "012" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_face_six__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "60000000000000000000000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_letter__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "a00000000000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_uppercase__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "A0000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_1_roll__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "f" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_256_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_50_rolls_above_limit__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "50151151500355541523152131531524531055551333221012" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_REJECTED "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__six_sides_50_fives__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "55555555555555555555555555555555555555555555555555" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_REJECTED "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_39_nines__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "999999999999999999999999999999999999999" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_REJECTED "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__one_side__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(1);
    command.set_rolls_argument({ "0000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_SIDES_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__seventeen_sides__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(17);
    command.set_rolls_argument({ "0000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_SIDES_INVALID "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
