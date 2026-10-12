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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(dice_entropy__invoke)

// Note: Test vectors match output from https://frozensecurity.com/tools/dice-entropy/

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__okay_output1)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "12345612345612345612345612345612345612345612345612" });
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT("184ec4bed56eb86aacaaa224b5672f45\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__okay_output2)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "12312312312312312312312334456554123341234326545643" });
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT("16a058b2bb69f1d15973a0c73d21b598\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__okay_output3)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "12312312312312444444444444446554123341234326545643" });
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT("16a058b2c4183470b20a7cd360e1b598\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__okay_output4)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "11111111111111111111111111111111111111111111111111" });
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT("00000000000000000000000000000000\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__okay_output5)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "1234561234561234561234561234561234561234561234561212345612345612345612345612345612345612345612345612" });
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT("39bd194e3b989d612e6ed5bf485bae121aa45fa1718ea167dd5ea224b5672f45\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__okay_output6)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "1231231231231231231231233445655412334123432654564312312312312312312312312334456554123341234326545643" });
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT("35beb4dc84e442e9fa6a56f5ae9176214cdbadaf5a78f8a6cad3a0c73d21b598\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__okay_output7)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "1231231231231244444444444444655412334123432654564312312312312312444444444444446554123341234326545643" });
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT("35beb4dc9982da244aded20982951b2d87ff7eed3b148246236a7cd360e1b598\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__okay_output8)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" });
   BX_REQUIRE_OKAY(command.invoke(output, error));
   BX_REQUIRE_OUTPUT("0000000000000000000000000000000000000000000000000000000000000000\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__error_input1)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "1" });
   BX_REQUIRE_FAILURE(command.invoke(output, error));
   BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__error_input2)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "123456123456123456123456123456123456123456123456123" });
   BX_REQUIRE_FAILURE(command.invoke(output, error));
   BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__error_input3)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "1234561234561234561234561234561234561234561234561" });
   BX_REQUIRE_FAILURE(command.invoke(output, error));
   BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__error_input4)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "12312312312312444444444444446554123341234326545643123123123123124444444444444465541233412343265456431" });
   BX_REQUIRE_FAILURE(command.invoke(output, error));
   BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__error_input5)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "123123123123124444444444444465541233412343265456431231231231231244444444444444655412334123432654564" });
   BX_REQUIRE_FAILURE(command.invoke(output, error));
   BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BOOST_AUTO_TEST_CASE(dice_entropy__invoke__error_input6)
{
   BX_DECLARE_COMMAND(dice_entropy);
   command.set_rolls_argument({ "7111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" });
   BX_REQUIRE_FAILURE(command.invoke(output, error));
   BX_REQUIRE_ERROR(BX_DICE_ROLLS_INVALID "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
