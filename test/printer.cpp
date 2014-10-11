/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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

#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <bitcoin/explorer.hpp>

using namespace bc::explorer;

BOOST_AUTO_TEST_SUITE(utility)
BOOST_AUTO_TEST_SUITE(utility__printer)

#define BX_APPLICATION "BX"
#define BX_COMMAND "COMMAND"
#define BX_CATEGORY "CATEGORY"
#define BX_DESCRIPTION "DESCRIPTION"

#define BX_PRINTER_SETUP_ARGUMENTS(initializer) \
    options_metadata options; \
    arguments_metadata arguments; \
    initializer; \
    printer help(BX_APPLICATION, BX_CATEGORY, BX_COMMAND, BX_DESCRIPTION, arguments, options)

#define BX_PRINTER_SETUP() \
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options())

#define BX_PRINTER_INITIALIZE(number_of_parameters, number_of_names) \
    help.initialize(); \
    BOOST_REQUIRE_EQUAL(help.get_parameters().size(), number_of_parameters); \
    BOOST_REQUIRE_EQUAL(help.get_argument_names().size(), number_of_names)

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__columnize)

BOOST_AUTO_TEST_CASE(printer__columnize__paragraph_empty_width_0__empty)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("", 0);
    BOOST_REQUIRE_EQUAL(rows.size(), 0);
}

BOOST_AUTO_TEST_CASE(printer__columnize__paragraph_empty_width_1__empty)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("", 1);
    BOOST_REQUIRE_EQUAL(rows.size(), 0);
}

BOOST_AUTO_TEST_CASE(printer__columnize__short_word_width_10__one_word_row)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("foo", 10);
    BOOST_REQUIRE_EQUAL(rows.size(), 1);
    BOOST_REQUIRE_EQUAL(rows.front(), "foo");
}

BOOST_AUTO_TEST_CASE(printer__columnize__two_short_words_width_10__two_word_row)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("foo bar", 10);
    BOOST_REQUIRE_EQUAL(rows.size(), 1);
    BOOST_REQUIRE_EQUAL(rows.front(), "foo bar");
}

BOOST_AUTO_TEST_CASE(printer__columnize__overflow_width_10__two_rows)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("foo bar overflow", 10);
    BOOST_REQUIRE_EQUAL(rows.size(), 2);
    BOOST_REQUIRE_EQUAL(rows[0], "foo bar");
    BOOST_REQUIRE_EQUAL(rows[1], "overflow");
}

BOOST_AUTO_TEST_CASE(printer__columnize__first_word_overflow_width_10__two_rows)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("morethantenchars foo bar", 10);
    BOOST_REQUIRE_EQUAL(rows.size(), 2);
    BOOST_REQUIRE_EQUAL(rows[0], "morethantenchars");
    BOOST_REQUIRE_EQUAL(rows[1], "foo bar");
}

BOOST_AUTO_TEST_CASE(printer__columnize__middle_word_overflow_width_10__three_rows)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("foo bar morethantenchars test", 10);
    BOOST_REQUIRE_EQUAL(rows.size(), 3);
    BOOST_REQUIRE_EQUAL(rows[0], "foo bar");
    BOOST_REQUIRE_EQUAL(rows[1], "morethantenchars");
    BOOST_REQUIRE_EQUAL(rows[2], "test");
}

BOOST_AUTO_TEST_CASE(printer__columnize__last_word_overflow_width_10__two_rows)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("foo bar morethantenchars", 10);
    BOOST_REQUIRE_EQUAL(rows.size(), 2);
    BOOST_REQUIRE_EQUAL(rows[0], "foo bar");
    BOOST_REQUIRE_EQUAL(rows[1], "morethantenchars");
}

BOOST_AUTO_TEST_CASE(printer__columnize__excess_whitespace_width_10__whitespace_removed)
{
    BX_PRINTER_SETUP();
    auto rows = help.columnize("  \tfoo   bar \n\n  morethantenchars\r\n  ", 10);
    BOOST_REQUIRE_EQUAL(rows.size(), 2);
    BOOST_REQUIRE_EQUAL(rows[0], "foo bar");
    BOOST_REQUIRE_EQUAL(rows[1], "morethantenchars");
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_parameters_table)

BOOST_AUTO_TEST_CASE(printer__format_parameters_table__positional_empty__empty)
{
    BX_PRINTER_SETUP();
    BOOST_REQUIRE_EQUAL(help.format_parameters_table(true), "");
}

BOOST_AUTO_TEST_CASE(printer__format_parameters_table__named_empty__empty)
{
    BX_PRINTER_SETUP();
    BOOST_REQUIRE_EQUAL(help.format_parameters_table(false), "");
}

BOOST_AUTO_TEST_CASE(printer__format_parameters_table__positional_three_options__empty)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("long", "Long name only.")
        ("short_long,s", "Long and short name.")
        (",m", "Short name only."));
    BX_PRINTER_INITIALIZE(3, 0);
    BOOST_REQUIRE_EQUAL(help.format_parameters_table(true), "");
}

BOOST_AUTO_TEST_CASE(printer__format_parameters_table__named_three_options__three_options)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("long", "Long name only.")
        ("short_long,s", "Long and short name.")
        (",m", "Short name only."));
    BX_PRINTER_INITIALIZE(3, 0);
    BOOST_REQUIRE_EQUAL(help.format_parameters_table(false),
        "--long                  Long name only.                                        \n"
        "-s [ --short_long ]     Long and short name.                                   \n"
        "-m                      Short name only.                                       \n"
    );
}

BOOST_AUTO_TEST_CASE(printer__format_parameters_table__named_three_options_two_arguments__three_options)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("first,f", "First option description.")
        ("second,x", "Second option description.")
        ("third", "Third option description.");
        arguments.add("forty-two", 42);
        arguments.add("THIRD", -1));
    BX_PRINTER_INITIALIZE(3, 2);
    BOOST_REQUIRE_EQUAL(help.format_parameters_table(false),
        "-f [ --first ]          First option description.                              \n"
        "-x [ --second ]         Second option description.                             \n"
        "--third                 Third option description.                              \n"
    );
}

BOOST_AUTO_TEST_CASE(printer__format_parameters_table__named_three_options_three_arguments__one_option)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("first,f", "First option description.")
        ("second,x", "Second option description.")
        ("THIRD", "Third option description.");
        arguments.add("FIRST", 1);
        arguments.add("second", 42);
        arguments.add("THIRD", -1));
    BX_PRINTER_INITIALIZE(3, 3);
    BOOST_REQUIRE_EQUAL(help.format_parameters_table(false),
        "-f [ --first ]          First option description.                              \n"
    );
}

BOOST_AUTO_TEST_CASE(printer__format_parameters_table__positional_three_options_three_arguments__two_options)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("first,f", "First option description.")
        ("second,x", "Second option description.")
        ("third", "Third option description.");
        arguments.add("FIRST", 1);
        arguments.add("second", 42);
        arguments.add("third", -1));
    BX_PRINTER_INITIALIZE(3, 3);
    BOOST_REQUIRE_EQUAL(help.format_parameters_table(true),
        "-x [ --second ]         Second option description.                             \n"
        "--third                 Third option description.                              \n"
    );
}

BOOST_AUTO_TEST_CASE(printer__format_parameters_table__positional_three_options_three_arguments_overflow__two_options_overflow)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("first,f", "First option description.")
        ("second,x", 
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
            "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut "
            "enim ad minim veniam, quis nostrud exercitation ullamco laboris "
            "nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor "
            "in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
            "nulla pariatur. Excepteur sint occaecat cupidatat non proident, "
            "sunt in culpa qui officia deserunt mollit anim id est laborum.")
        ("third", "Third option description.");
    arguments.add("FIRST", 1);
    arguments.add("second", 42);
    arguments.add("third", -1));
    BX_PRINTER_INITIALIZE(3, 3);
    auto table = help.format_parameters_table(true);
    BOOST_REQUIRE_EQUAL(table,
        "-x [ --second ]         Lorem ipsum dolor sit amet, consectetur adipiscing     \n"
        "                        elit, sed do eiusmod tempor incididunt ut labore et    \n"
        "                        dolore magna aliqua. Ut enim ad minim veniam, quis     \n"
        "                        nostrud exercitation ullamco laboris nisi ut aliquip ex\n"
        "                        ea commodo consequat. Duis aute irure dolor in         \n"
        "                        reprehenderit in voluptate velit esse cillum dolore eu \n"
        "                        fugiat nulla pariatur. Excepteur sint occaecat         \n"
        "                        cupidatat non proident, sunt in culpa qui officia      \n"
        "                        deserunt mollit anim id est laborum.                   \n"
        "--third                 Third option description.                              \n"
    );
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__generate_argument_names)

#define BX_PRINTER_GENERATE_ARGUMENT_NAMES(number_of_names) \
    help.generate_argument_names(); \
    BOOST_REQUIRE_EQUAL(help.get_argument_names().size(), number_of_names)

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__empty_arguments_empty_options__empty)
{
    BX_PRINTER_SETUP();
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(0);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__empty_arguments_multiple_options__empty)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("long", "Long name only.")
        ("short_long,s", "Long and short name.")
        (",m", "Short name only."));
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(0);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_1__one_name_1)
{
    BX_PRINTER_SETUP_ARGUMENTS(arguments.add("one", 1));
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(help.get_argument_names()[0].first == "one");
    BOOST_REQUIRE(help.get_argument_names()[0].second == 1);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_42__one_name_42)
{
    BX_PRINTER_SETUP_ARGUMENTS(arguments.add("forty-two", 42));
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(help.get_argument_names()[0].first == "forty-two");
    BOOST_REQUIRE(help.get_argument_names()[0].second == 42);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_max_arguments__one_name_max_arguments)
{
    BX_PRINTER_SETUP_ARGUMENTS(arguments.add("max_arguments", printer::max_arguments));
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(help.get_argument_names()[0].first == "max_arguments");
    BOOST_REQUIRE(help.get_argument_names()[0].second == printer::max_arguments);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_max_arguments_plus_1__one_name_negative_1)
{
    BX_PRINTER_SETUP_ARGUMENTS(arguments.add("max_arguments+1", printer::max_arguments + 1));
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(help.get_argument_names()[0].first == "max_arguments+1");
    BOOST_REQUIRE(help.get_argument_names()[0].second == -1);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_negative_1__one_name_negative_1)
{
    BX_PRINTER_SETUP_ARGUMENTS(arguments.add("negative-one", -1));
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(help.get_argument_names()[0].first == "negative-one");
    BOOST_REQUIRE(help.get_argument_names()[0].second == -1);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__multiple_arguments__expected_names)
{
    BX_PRINTER_SETUP_ARGUMENTS(
        arguments.add("forty-two", 42);
        arguments.add("max_arguments", printer::max_arguments));
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(2);
    BOOST_REQUIRE(help.get_argument_names()[0].first == "forty-two");
    BOOST_REQUIRE(help.get_argument_names()[0].second == 42);
    BOOST_REQUIRE(help.get_argument_names()[1].first == "max_arguments");
    BOOST_REQUIRE(help.get_argument_names()[1].second == printer::max_arguments);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__multiple_arguments_negative_1__expected_names)
{
    BX_PRINTER_SETUP_ARGUMENTS(
        arguments.add("forty-two", 42);
        arguments.add("max_arguments", printer::max_arguments);
        arguments.add("negative-one", -1));
    BX_PRINTER_GENERATE_ARGUMENT_NAMES(3);
    BOOST_REQUIRE(help.get_argument_names()[0].first == "forty-two");
    BOOST_REQUIRE(help.get_argument_names()[0].second == 42);
    BOOST_REQUIRE(help.get_argument_names()[1].first == "max_arguments");
    BOOST_REQUIRE(help.get_argument_names()[1].second == printer::max_arguments);
    BOOST_REQUIRE(help.get_argument_names()[2].first == "negative-one");
    BOOST_REQUIRE(help.get_argument_names()[2].second == -1);
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__generate_parameters)

#define BX_PRINTER_GENERATE_PARAMETERS(number_of_parameters) \
    help.generate_parameters(); \
    BOOST_REQUIRE_EQUAL(help.get_parameters().size(), number_of_parameters)

BOOST_AUTO_TEST_CASE(printer__generate_parameters__empty__empty_parameters)
{
    BX_PRINTER_SETUP();
    BX_PRINTER_GENERATE_PARAMETERS(0);
}

BOOST_AUTO_TEST_CASE(printer__generate_parameters__one_option__one_parameter)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("foo_bar,f", "Foobar option name."));
    BX_PRINTER_GENERATE_PARAMETERS(1);
    BOOST_REQUIRE(help.get_parameters()[0].get_short_name() == 'f');
}

BOOST_AUTO_TEST_CASE(printer__generate_parameters__multitple_options__expected_parameters)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("first,f", "First option description.")
        ("second,x", "Second option description.")
        ("third", "Third option description."));
    BX_PRINTER_GENERATE_PARAMETERS(3);
    BOOST_REQUIRE(help.get_parameters()[0].get_canonical_name() == "--first");
    BOOST_REQUIRE(help.get_parameters()[1].get_short_name() == 'x');
    BOOST_REQUIRE(help.get_parameters()[2].get_description() == "Third option description.");
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__initialize)

BOOST_AUTO_TEST_CASE(printer__initialize__multitple_options__expected_parameters)
{
    BX_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("first,f", "First option description.")
        ("second,x", "Second option description.")
        ("third", "Third option description.");
        arguments.add("forty-two", 42);
        arguments.add("negative-one", -1));
    BX_PRINTER_INITIALIZE(3, 2);
    BOOST_REQUIRE(help.get_parameters()[0].get_canonical_name() == "--first");
    BOOST_REQUIRE(help.get_parameters()[1].get_short_name() == 'x');
    BOOST_REQUIRE(help.get_parameters()[2].get_description() == "Third option description.");
    BOOST_REQUIRE(help.get_argument_names()[0].first == "forty-two");
    BOOST_REQUIRE(help.get_argument_names()[0].second == 42);
    BOOST_REQUIRE(help.get_argument_names()[1].first == "negative-one");
    BOOST_REQUIRE(help.get_argument_names()[1].second == -1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END() // utility__printer
BOOST_AUTO_TEST_SUITE_END() // utility