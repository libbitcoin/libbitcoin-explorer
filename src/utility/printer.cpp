/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include "precompile.hpp"
#include <bitcoin/explorer/utility/printer.hpp>

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/explorer/define.hpp>

// TODO: obtain from XML resource as localized text.
// NOTE: in the usage format "bx command" is the first parameter.
#define BX_PRINTER_USAGE_FORMAT "\nUSAGE: %1% %2%\n"
#define BX_PRINTER_USAGE_OPTION_OPTIONAL_TOGGLE_FORMAT "[-%1%]"
#define BX_PRINTER_USAGE_OPTION_REQUIRED_VALUE_FORMAT "-%1% ARG"
#define BX_PRINTER_USAGE_OPTION_OPTIONAL_VALUE_FORMAT "[-%1% ARG]"
#define BX_PRINTER_USAGE_OPTION_OPTIONAL_VALUE_VARIABLE_FORMAT "[-%1% ARG]..."
#define BX_PRINTER_USAGE_ARGUMENT_REQUIRED_FORMAT "%1%"
#define BX_PRINTER_USAGE_ARGUMENT_OPTIONAL_FORMAT "[%1%]"
#define BX_PRINTER_USAGE_ARGUMENT_OPTIONAL_VARIABLE_FORMAT "[%1%]..."

#define BX_PRINTER_SUMMARY_HEADER "\n-- Option Descriptions --\n"

#define BX_PRINTER_ARGUMENTS_HEADER "\nPositional Arguments:\n"
#define BX_PRINTER_ARGUMENT_FORMAT "%1% \"%2%\"\n"

#define BX_PRINTER_OPTIONS_HEADER "\nOption Arguments:\n"
#define BX_PRINTER_OPTION_SHORT_FORMAT "-%1% %2\n"
#define BX_PRINTER_OPTION_LONG_FORMAT "--%1% %2\n"
#define BX_PRINTER_OPTION_SHORT_LONG_FORMAT "-%1% [ --%2% ] %3\n"

using namespace bc::explorer;

/* Formatters */

// TODO: implement, component test.
std::string printer::format_help_arguments()
{
    return "format_help_arguments";
}

// TODO: implement, component test.
std::string printer::format_help_options()
{
    return "format_help_options";
}

// TODO: component test.
std::string printer::format_usage()
{
    auto usage = boost::format(BX_PRINTER_USAGE_FORMAT) %
        get_application() % format_usage_parameters();
    return usage.str();
}

// TODO: implement, component test.
std::string printer::format_usage_arguments()
{
    return "format_usage_arguments";
}

// TODO: component test.
std::string printer::format_usage_options()
{
    std::vector<std::string> words;
    words.push_back(format_usage_toggle_options());
    words.push_back(format_usage_value_options());
    std::string sentence;
    join(words, sentence);
    return sentence;
}

// TODO: component test.
std::string printer::format_usage_parameters()
{
    std::vector<std::string> words;
    words.push_back(format_usage_options());
    words.push_back(format_usage_arguments());
    std::string sentence;
    join(words, sentence);
    return sentence;
}

// TODO: implement, component test.
std::string printer::format_usage_toggle_options()
{
    return "format_usage_toggle_options";
}

// TODO: implement, component test.
std::string printer::format_usage_value_options()
{
    return "format_usage_value_options";
}

/* Helpers */

// TODO: order collection? component test.
void printer::initialize()
{
    auto options = get_options();
    auto parameters = get_parameters();
    auto arguments = get_arguments();

    // TODO: build list of names.
    auto argument_names = get_argument_names();

    parameter param;
    for (auto option_ptr: options.options())
    {
        param.initialize(*option_ptr, argument_names);
        parameters.push_back(param);
    }
}

/* Printers */

// TODO: component test.
void printer::print_help()
{
    // --Option Descriptions --
    // ...
    get_output()
        << BX_PRINTER_SUMMARY_HEADER
        << BX_PRINTER_ARGUMENTS_HEADER
        << format_help_arguments()
        << BX_PRINTER_OPTIONS_HEADER
        << format_help_options();
}

// TODO: component test.
void printer::print_usage()
{
    // USAGE: bx command [-hvt] [-w ARG]... [-m ARG] - n ARG ADD [LIKE]...
    get_output() << format_usage();
}