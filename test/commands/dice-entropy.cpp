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

BC_AUTO_TEST_CASE(dice_entropy__invoke__50_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "12345612345612345612345612345612345612345612345612" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("184ec4bed56eb86aacaaa224b5672f45\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__50_mixed_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "12312312312312312312312334456554123341234326545643" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("16a058b2bb69f1d15973a0c73d21b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__50_rolls_run_of_fours__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "12312312312312444444444444446554123341234326545643" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("16a058b2c4183470b20a7cd360e1b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__50_ones__okay_zero_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "11111111111111111111111111111111111111111111111111" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("00000000000000000000000000000000\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__100_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "1234561234561234561234561234561234561234561234561212345612345612345612345612345612345612345612345612" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("39bd194e3b989d612e6ed5bf485bae121aa45fa1718ea167dd5ea224b5672f45\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__100_mixed_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "1231231231231231231231233445655412334123432654564312312312312312312312312334456554123341234326545643" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("35beb4dc84e442e9fa6a56f5ae9176214cdbadaf5a78f8a6cad3a0c73d21b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__100_rolls_run_of_fours__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "1231231231231244444444444444655412334123432654564312312312312312444444444444446554123341234326545643" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("35beb4dc9982da244aded20982951b2d87ff7eed3b148246236a7cd360e1b598\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__100_ones__okay_zero_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0000000000000000000000000000000000000000000000000000000000000000\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__50_rolls_at_limit__okay_maximum_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "61262262611466652634263242642635642166662444332122" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__100_rolls_at_limit__okay_maximum_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "6263365546524225314413253522255442433336134252134625323511345453215331453612416422433556351254153322" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__two_sides_128_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(2);
    command.set_rolls_argument({ "12121212121212121212121212121212121212121212121212121212121212121212121212121212121212121212121212121212121212121212121212121212" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("55555555555555555555555555555555\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__two_sides_128_ones__okay_zero_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(2);
    command.set_rolls_argument({ "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("00000000000000000000000000000000\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__four_sides_64_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(4);
    command.set_rolls_argument({ "1234123412341234123412341234123412341234123412341234123412341234" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b1b\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_39_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "123456789112345678911234567891123456789" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0949b0eb93f3a5ed0a467f064c9fd94e\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_32_rolls__okay_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "123456789abcdefg123456789abcdefg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0123456789abcdef0123456789abcdef\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__sixteen_sides_64_maximum_rolls__okay_maximum_output)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(16);
    command.set_rolls_argument({ "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__one_roll__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "1" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__51_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "123456123456123456123456123456123456123456123456123" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__49_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "1234561234561234561234561234561234561234561234561" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__101_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "12312312312312444444444444446554123341234326545643123123123123124444444444444465541233412343265456431" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__99_rolls__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "123123123123124444444444444465541233412343265456431231231231231244444444444444655412334123432654564" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__face_seven_on_six_sides__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "7111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__50_rolls_above_limit__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(6);
    command.set_rolls_argument({ "61262262611466652634263242642635642166662444332123" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__ten_sides_39_rolls_above_limit__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__letter_on_ten_sides__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(10);
    command.set_rolls_argument({ "b11111111111111111111111111111111111111" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__one_side__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(1);
    command.set_rolls_argument({ "11111111111111111111111111111111111111111111111111" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_SIDES_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_entropy__invoke__seventeen_sides__failure_error)
{
    BX_DECLARE_COMMAND(dice_entropy);
    command.set_sides_option(17);
    command.set_rolls_argument({ "11111111111111111111111111111111" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_SIDES_INVALID "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
