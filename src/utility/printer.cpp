/**
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

#include <bitcoin/explorer/utility/printer.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/explorer/define.hpp>

// TODO: obtain from XML resource as localized text.
// NOTE: in the usage format "bx command" is the first parameter.
#define BX_PRINTER_USAGE_FORMAT "\nUsage: %1% %2%\n"
#define BX_PRINTER_USAGE_OPTION_OPTIONAL_TOGGLE_FORMAT "[-%1%]"
#define BX_PRINTER_USAGE_OPTION_REQUIRED_VALUE_FORMAT "-%1% ARG"
#define BX_PRINTER_USAGE_OPTION_OPTIONAL_VALUE_FORMAT "[-%1% ARG]"
#define BX_PRINTER_USAGE_OPTION_OPTIONAL_VALUE_VARIABLE_FORMAT "[-%1% ARG]..."
#define BX_PRINTER_USAGE_ARGUMENT_REQUIRED_FORMAT "%1%"
#define BX_PRINTER_USAGE_ARGUMENT_OPTIONAL_FORMAT "[%1%]"
#define BX_PRINTER_USAGE_ARGUMENT_OPTIONAL_VARIABLE_FORMAT "[%1%]..."

#define BX_PRINTER_SUMMARY_HEADER "\n-- Parameter Descriptions --\n"

#define BX_PRINTER_ARGUMENTS_HEADER "\nArguments (positional):\n"
#define BX_PRINTER_ARGUMENT_FORMAT "%1% \"%2%\"\n"

#define BX_PRINTER_OPTIONS_HEADER "\nOptions (named):\n"
#define BX_PRINTER_OPTION_SHORT_FORMAT "-%1% %2\n"
#define BX_PRINTER_OPTION_LONG_FORMAT "--%1% %2\n"
#define BX_PRINTER_OPTION_SHORT_LONG_FORMAT "-%1% [ --%2% ] %3\n"

/*
    USAGE: bx command [-hvt] [-w ARG]... [-m ARG] -n ARG ADD [LIKE]...

    -- Option Descriptions --

    Positional Arguments:
    ADD "additional options"
    LIKE "this"

    Option Arguments:
    -h [--help] Print help messages
    -v [--verbose] Print words with verbosity
    -w [--word] Words for the sentence, specify multiple times
    -t Just a temp option that does very little
    -n [--necessary] Give me anything
    -m [--manual] Extract value manually
*/

using namespace bc::explorer;

printer::printer(std::ostream& output, options_metadata& options,
    arguments_metadata& arguments, const std::string& application)
  : application_(application), arguments_(arguments), options_(options),
    output_(output)
{
}

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

/* Initialization */

// 100% component tested.
// This method just gives us a copy of arguments_metadata private state.
// It would be nice if instead that state was public.
void printer::generate_argument_names()
{
    // Member values
    const auto& arguments = get_arguments();
    auto& argument_names = get_argument_names();
    const auto max_total_arguments = arguments.max_total_count();

    // Temporary values
    std::string argument_name;
    std::string previous_argument_name;
    int max_previous_argument = 0;

    // We must enumerate all arguments to get the full set of names and counts.
    for (unsigned int position = 0; position < max_total_arguments && 
        max_previous_argument <= max_arguments; ++position)
    {
        argument_name = arguments.name_for_position(position);

        // Initialize the first name as having a zeroth instance.
        if (max_previous_argument == 0)
            previous_argument_name = argument_name;

        // This is the first name or a duplicate of the last name.
        if (argument_name == previous_argument_name)
        {
            ++max_previous_argument;
            continue;
        }

        // Save the previous name.
        argument_pair pair(previous_argument_name, max_previous_argument);
        argument_names.push_back(pair);

        previous_argument_name = argument_name;
        max_previous_argument = 1;
    }

    // Save the last argument (if there is one).
    if (max_previous_argument > 0)
    {
        if (max_previous_argument > max_arguments)
            max_previous_argument = -1;

        argument_pair pair(previous_argument_name, max_previous_argument);
        argument_names.push_back(pair);
    }
}

// 100% component tested.
void printer::generate_parameters()
{
    const auto& argument_names = get_argument_names();
    const auto& options = get_options();
    auto& parameters = get_parameters();

    parameter param;
    for (auto option_ptr: options.options())
    {
        param.initialize(*option_ptr, argument_names);
        parameters.push_back(param);
    }
}

// 100% component tested.
void printer::initialize()
{
    generate_argument_names();
    generate_parameters();
}

/* Printers */

// TODO: component test.
void printer::print_help()
{
    // -- Option Descriptions --
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