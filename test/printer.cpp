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

#define BX_APPLICATION "bx"
#define BX_COMMAND "COMMAND"

#define BX_TEST_PRINTER_SETUP_ARGUMENTS(initializer) \
    options_metadata options; \
    arguments_metadata arguments; \
    initializer; \
    printer test_printer(BX_APPLICATION, BX_COMMAND, arguments, options)

#define BX_TEST_PRINTER_SETUP() \
    BX_TEST_PRINTER_SETUP_ARGUMENTS(options.add_options())

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_help_arguments)

BOOST_AUTO_TEST_CASE(printer__format_help_arguments__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_help_options)

BOOST_AUTO_TEST_CASE(printer__format_help_options__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_usage)

BOOST_AUTO_TEST_CASE(printer__format_usage__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_usage_arguments)

BOOST_AUTO_TEST_CASE(printer__format_usage_arguments__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_usage_options)

BOOST_AUTO_TEST_CASE(printer__format_usage_options__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_usage_parameters)

BOOST_AUTO_TEST_CASE(printer__format_usage_parameters__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_usage_toggle_options)

BOOST_AUTO_TEST_CASE(printer__format_usage_toggle_options__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__format_usage_value_options)

BOOST_AUTO_TEST_CASE(printer__format_usage_value_options__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__generate_argument_names)

#define BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(number_of_names) \
    test_printer.generate_argument_names(); \
    BOOST_REQUIRE(test_printer.get_argument_names().size() == number_of_names)

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__empty_arguments_empty_options__empty)
{
    BX_TEST_PRINTER_SETUP();
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(0);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__empty_arguments_multiple_options__empty)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("short_long,s", "Long and short name.")
        (",m", "Short name only."));
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(0);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_1__one_name_1)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(arguments.add("one", 1));
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(test_printer.get_argument_names()[0].first == "one");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].second == 1);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_42__one_name_42)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(arguments.add("forty-two", 42));
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(test_printer.get_argument_names()[0].first == "forty-two");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].second == 42);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_max_arguments__one_name_max_arguments)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(arguments.add("max_arguments", printer::max_arguments));
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(test_printer.get_argument_names()[0].first == "max_arguments");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].second == printer::max_arguments);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_max_arguments_plus_1__one_name_negative_1)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(arguments.add("max_arguments+1", printer::max_arguments + 1));
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(test_printer.get_argument_names()[0].first == "max_arguments+1");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].second == -1);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__one_argument_negative_1__one_name_negative_1)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(arguments.add("negative-one", -1));
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(1);
    BOOST_REQUIRE(test_printer.get_argument_names()[0].first == "negative-one");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].second == -1);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__multiple_arguments__expected_names)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(
        arguments.add("forty-two", 42);
        arguments.add("max_arguments", printer::max_arguments));
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(2);
    BOOST_REQUIRE(test_printer.get_argument_names()[0].first == "forty-two");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].second == 42);
    BOOST_REQUIRE(test_printer.get_argument_names()[1].first == "max_arguments");
    BOOST_REQUIRE(test_printer.get_argument_names()[1].second == printer::max_arguments);
}

BOOST_AUTO_TEST_CASE(printer__generate_argument_names__multiple_arguments_negative_1__expected_names)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(
        arguments.add("forty-two", 42);
        arguments.add("max_arguments", printer::max_arguments);
        arguments.add("negative-one", -1));
    BX_TEST_PRINTER_GENERATE_ARGUMENT_NAMES(3);
    BOOST_REQUIRE(test_printer.get_argument_names()[0].first == "forty-two");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].second == 42);
    BOOST_REQUIRE(test_printer.get_argument_names()[1].first == "max_arguments");
    BOOST_REQUIRE(test_printer.get_argument_names()[1].second == printer::max_arguments);
    BOOST_REQUIRE(test_printer.get_argument_names()[2].first == "negative-one");
    BOOST_REQUIRE(test_printer.get_argument_names()[2].second == -1);
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__generate_parameters)

#define BX_TEST_PRINTER_GENERATE_PARAMETERS(number_of_parameters) \
    test_printer.generate_parameters(); \
    BOOST_REQUIRE(test_printer.get_parameters().size() == number_of_parameters)

BOOST_AUTO_TEST_CASE(printer__generate_parameters__empty__empty_parameters)
{
    BX_TEST_PRINTER_SETUP();
    BX_TEST_PRINTER_GENERATE_PARAMETERS(0);
}

BOOST_AUTO_TEST_CASE(printer__generate_parameters__one_option__one_parameter)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("foo_bar,f", "Foobar option name."));
    BX_TEST_PRINTER_GENERATE_PARAMETERS(1);
    BOOST_REQUIRE(test_printer.get_parameters()[0].get_short_name() == 'f');
}

BOOST_AUTO_TEST_CASE(printer__generate_parameters__multitple_options__expected_parameters)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("first,f", "First option description.")
        ("second,x", "Second option description.")
        ("third", "Third option description."));
    BX_TEST_PRINTER_GENERATE_PARAMETERS(3);
    BOOST_REQUIRE(test_printer.get_parameters()[0].get_canonical_name() == "--first");
    BOOST_REQUIRE(test_printer.get_parameters()[1].get_short_name() == 'x');
    BOOST_REQUIRE(test_printer.get_parameters()[2].get_description() == "Third option description.");
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__initialize)

#define BX_TEST_PRINTER_INITIALIZE(number_of_parameters, number_of_names) \
    test_printer.initialize(); \
    BOOST_REQUIRE(test_printer.get_parameters().size() == number_of_parameters); \
    BOOST_REQUIRE(test_printer.get_argument_names().size() == number_of_names)

BOOST_AUTO_TEST_CASE(printer__initialize__multitple_options__expected_parameters)
{
    BX_TEST_PRINTER_SETUP_ARGUMENTS(options.add_options()
        ("first,f", "First option description.")
        ("second,x", "Second option description.")
        ("third", "Third option description.");
        arguments.add("forty-two", 42);
        arguments.add("negative-one", -1));
    BX_TEST_PRINTER_INITIALIZE(3, 2);
    BOOST_REQUIRE(test_printer.get_parameters()[0].get_canonical_name() == "--first");
    BOOST_REQUIRE(test_printer.get_parameters()[1].get_short_name() == 'x');
    BOOST_REQUIRE(test_printer.get_parameters()[2].get_description() == "Third option description.");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].first == "forty-two");
    BOOST_REQUIRE(test_printer.get_argument_names()[0].second == 42);
    BOOST_REQUIRE(test_printer.get_argument_names()[1].first == "negative-one");
    BOOST_REQUIRE(test_printer.get_argument_names()[1].second == -1);
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(printer__print)

BOOST_AUTO_TEST_CASE(printer__print__todo)
{
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()