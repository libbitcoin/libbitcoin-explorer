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
BC_AUTO_TEST_SUITE(dice_rolls__invoke)

BC_AUTO_TEST_CASE(dice_rolls__invoke__six_sides_128_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(6);
    command.set_bits_option(128);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("52\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__six_sides_256_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(6);
    command.set_bits_option(256);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("102\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__six_sides_136_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(6);
    command.set_bits_option(136);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("53\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__two_sides_128_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(2);
    command.set_bits_option(128);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("128\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__eight_sides_128_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(8);
    command.set_bits_option(128);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("43\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__ten_sides_128_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(10);
    command.set_bits_option(128);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("40\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__ten_sides_256_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(10);
    command.set_bits_option(256);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("79\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__twelve_sides_128_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(12);
    command.set_bits_option(128);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("36\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__sixteen_sides_128_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(16);
    command.set_bits_option(128);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("32\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__sixteen_sides_512_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(16);
    command.set_bits_option(512);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("128\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__three_sides_8_bits__okay_output)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(3);
    command.set_bits_option(8);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("10\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__zero_bits__failure_error)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(6);
    command.set_bits_option(0);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_BITS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__12_bits__failure_error)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(6);
    command.set_bits_option(12);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_BITS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__520_bits__failure_error)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(6);
    command.set_bits_option(520);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_BITS_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__one_side__failure_error)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(1);
    command.set_bits_option(128);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_SIDES_INVALID "\n");
}

BC_AUTO_TEST_CASE(dice_rolls__invoke__seventeen_sides__failure_error)
{
    BX_DECLARE_COMMAND(dice_rolls);
    command.set_sides_option(17);
    command.set_bits_option(128);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_DICE_ROLLS_SIDES_INVALID "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
