/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/test/unit_test.hpp>
#include <sx/sx.hpp>

BOOST_AUTO_TEST_SUITE(console_line_out)

BOOST_AUTO_TEST_CASE(line_out_single_streams_line)
{
    std::stringstream stream;
    sx::line_out(stream, "World!");
    BOOST_REQUIRE(stream.str() == "World!\n");
}

BOOST_AUTO_TEST_CASE(line_out_single_offset_streams_offset)
{
    std::stringstream stream;
    sx::line_out(stream, "World!", 6);
    BOOST_REQUIRE(stream.str() == "      World!\n");
}

BOOST_AUTO_TEST_CASE(line_out_single_inset_streams_inset)
{
    std::stringstream stream;
    sx::line_out(stream, "World!", 6, "Hello");
    BOOST_REQUIRE(stream.str() == "Hello World!\n");
}

BOOST_AUTO_TEST_CASE(line_out_single_inset_equals_offset_streams_bump)
{
    std::stringstream stream;
    sx::line_out(stream, "World!", 5, "Hello");
    BOOST_REQUIRE(stream.str() == "HelloWorld!\n");
}

BOOST_AUTO_TEST_CASE(line_out_single_inset_exceeds_offset_streams_bump)
{
    std::stringstream stream;
    sx::line_out(stream, "World!", 4, "Hello");
    BOOST_REQUIRE(stream.str() == "HelloWorld!\n");
}

BOOST_AUTO_TEST_CASE(line_out_single_empty_streams_line_feed)
{
    std::stringstream stream;
    sx::line_out(stream, "");
    BOOST_REQUIRE(stream.str() == "\n");
}

BOOST_AUTO_TEST_CASE(line_out_multiple_streams_lines)
{
    auto lines = std::vector<const char*>(
    {
        { "My folks got me a bitchin' Camero," },
        { "With no insurance to match;" },
        { "So if I happen to run you down," },
        { "Please don't leave a scratch." }
    });
    std::stringstream stream;
    sx::line_out(stream, lines);
    BOOST_REQUIRE(stream.str() ==
        "My folks got me a bitchin' Camero,\n"
        "With no insurance to match;\n"
        "So if I happen to run you down,\n"
        "Please don't leave a scratch.\n");
}

BOOST_AUTO_TEST_CASE(line_out_multiple_offset_streams_offset)
{
    auto lines = std::vector<const char*>(
    {
        { "I ran over some old lady," },
        { "One night at the county fair;" },
        { "And I didn't get arrested," },
        { "Because my dad's the mayor." }
    });
    std::stringstream stream;
    sx::line_out(stream, lines, 15);
    BOOST_REQUIRE(stream.str() ==
        "               I ran over some old lady,\n"
        "               One night at the county fair;\n"
        "               And I didn't get arrested,\n"
        "               Because my dad's the mayor.\n");
}

BOOST_AUTO_TEST_CASE(line_out_multiple_inset_streams_inset)
{
    auto lines = std::vector<const char*>(
    {
        { "Bitchin' Camero, bitchin' Camero," },
        { "Doughnuts on your lawn;" },
        { "Bitchin' Camero, bitchin' Camero," },
        { "Tony Orlando and Dawn." }
    });
    std::stringstream stream;
    sx::line_out(stream, lines, 15, "Dead Milkmen");
    BOOST_REQUIRE(stream.str() ==
        "Dead Milkmen   Bitchin' Camero, bitchin' Camero,\n"
        "               Doughnuts on your lawn;\n"
        "               Bitchin' Camero, bitchin' Camero,\n"
        "               Tony Orlando and Dawn.\n");
}

BOOST_AUTO_TEST_CASE(line_out_multiple_inset_equals_offset_streams_bump)
{
    auto lines = std::vector<const char*>(
    {
        { "When I drive past the kids," },
        { "They all spit and cuss," },
        { "Because I've got a bitchin' Camero," },
        { "And they have to ride the bus." }
    });
    std::stringstream stream;
    sx::line_out(stream, lines, 12, "Dead Milkmen");
    BOOST_REQUIRE(stream.str() ==
        "Dead MilkmenWhen I drive past the kids,\n"
        "            They all spit and cuss,\n"
        "            Because I've got a bitchin' Camero,\n"
        "            And they have to ride the bus.\n");
}

BOOST_AUTO_TEST_CASE(line_out_multiple_inset_exceeds_offset_streams_overflow)
{
    auto lines = std::vector<const char*>(
    {
        { "Bitchin' Camero, bitchin' Camero," },
        { "Hey man where you headed?" },
        { "Bitchin' Camero, bitchin' Camero," },
        { "I don't want unleaded!" }
    });
    std::stringstream stream;
    sx::line_out(stream, lines, 10, "Dead Milkmen");
    BOOST_REQUIRE(stream.str() ==
        "Dead MilkmenBitchin' Camero, bitchin' Camero,\n"
        "          Hey man where you headed?\n"
        "          Bitchin' Camero, bitchin' Camero,\n"
        "          I don't want unleaded!\n");
}

BOOST_AUTO_TEST_CASE(line_out_multiple_none_streams_nothing)
{
    auto lines = std::vector<const char*>();
    std::stringstream stream;
    sx::line_out(stream, lines, 10, "Dead Milkmen");
    BOOST_REQUIRE(stream.str() == "");
}

BOOST_AUTO_TEST_CASE(line_out_multiple_empty_streams_inset)
{
    auto lines = std::vector<const char*>({ { "" } });
    std::stringstream stream;
    sx::line_out(stream, lines, 10, "Dead Milkmen");
    BOOST_REQUIRE(stream.str() == "Dead Milkmen\n");
}

BOOST_AUTO_TEST_SUITE_END()