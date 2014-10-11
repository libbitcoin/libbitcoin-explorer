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

// We are doing this because po::options_description.print() sucks.

#define BX_PRINTER_USAGE_FORMAT "\nUsage: %1% %2% %3%\n"

#define BX_PRINTER_USAGE_OPTION_TOGGLE_FORMAT "[-%1%]"
#define BX_PRINTER_USAGE_OPTION_REQUIRED_FORMAT "-%1% VALUE"
#define BX_PRINTER_USAGE_OPTION_OPTIONAL_FORMAT "[-%1% VALUE]"
#define BX_PRINTER_USAGE_OPTION_VARIABLE_FORMAT "[-%1% VALUE]..."

#define BX_PRINTER_USAGE_ARGUMENT_REQUIRED_FORMAT "%1%"
#define BX_PRINTER_USAGE_ARGUMENT_OPTIONAL_FORMAT "[%1%]"
#define BX_PRINTER_USAGE_ARGUMENT_VARIABLE_FORMAT "[%1%]..."

#define BX_PRINTER_DESCRIPTION_FORMAT "\n%1%\n"
#define BX_PRINTER_CATEGORY_FORMAT "\nCategery: %1%\n"

#define BX_PRINTER_OPTION_TABLE_HEADER "\nOptions (named):\n\n"
#define BX_PRINTER_ARGUMENT_TABLE_HEADER "\nArguments (positional):\n\n"

using namespace bc::explorer;

printer::printer(const std::string& application, const std::string& category,
    const std::string& command, const std::string& description,
    const arguments_metadata& arguments, const options_metadata& options)
  : application_(application), category_(category), command_(command),
    description_(description), arguments_(arguments), options_(options)
{
}

/* Formatters */

// 100% component tested.
static void enqueue_fragment(std::string& fragment,
    std::vector<std::string>& column)
{
    trim(fragment);
    if (!fragment.empty())
        column.push_back(fragment);
}

// 100% component tested.
std::vector<std::string> printer::columnize(const std::string& paragraph,
    size_t width)
{
    const auto words = split(paragraph);

    std::string fragment;
    std::vector<std::string> column;

    for (const auto& word: words)
    {
        if (word.length() + fragment.length() < width)
        {
            fragment += " " + word;
            continue;
        }

        enqueue_fragment(fragment, column);
        fragment = word;
    }

    enqueue_fragment(fragment, column);
    return column;
}

// 100% component tested.
// This formats to 80 char width as: [ 23 | ' ' | 55 | '\n' ]
std::string printer::format_parameters_table(bool positional)
{
    std::stringstream output;
    const auto& parameters = get_parameters();
    format table("%-23s %-55s\n");

    for (const auto& parameter: parameters)
    {
        // Skip positional arguments.
        if ((parameter.get_position() == -1 && positional) || 
            (parameter.get_position() != -1 && !positional))
            continue;

        // Get the formatted parameter name.
        std::string name(parameter.get_format_name());

        // Build a column for the description.
        const auto rows = columnize(parameter.get_description(), 55);

        // If there is no description the command is not output!
        for (const auto& row: rows)
        {
            output << table % name % row;

            // The name is only set in the first row.
            name = "";
        }
    }

    return output.str();
}

std::string printer::format_usage()
{
    // USAGE: bx COMMAND ([-hvt] -n VALUE [-m VALUE] [-w VALUE]...) (REQUIRED [OPTIONAL] [MULTIPLE]...)
    auto usage = format(BX_PRINTER_USAGE_FORMAT) % get_application() %
        get_command() % format_usage_parameters();
    return usage.str();
}

std::string printer::format_category()
{
    // CATEGORY: %1%\n
    auto category = format(BX_PRINTER_CATEGORY_FORMAT) % get_category();
    return category.str();
}

std::string printer::format_description()
{
    // DESCRIPTION: %1%\n
    auto description = format(BX_PRINTER_DESCRIPTION_FORMAT) % get_description();
    return description.str();
}

std::string printer::format_usage_parameters()
{
    //std::vector<std::string> words;

    //words.push_back(format_usage_toggle_options());
    //words.push_back(format_usage_required_options());
    //words.push_back(format_usage_optional_options());
    //words.push_back(format_usage_multivalued_options());

    //words.push_back(format_usage_required_arguments());
    //words.push_back(format_usage_optional_arguments());
    //words.push_back(format_usage_multivalued_arguments());

    //std::string sentence;
    //join(words, sentence);

    return "";
}

std::string printer::format_usage_toggle_options()
{
    return "format_usage_toggle_options";
}

std::string printer::format_usage_required_options()
{
    return "format_usage_required_options";
}

std::string printer::format_usage_optional_options()
{
    return "format_usage_optional_options";
}

std::string printer::format_usage_multivalued_options()
{
    return "format_usage_multivalue_options";
}

std::string printer::format_usage_required_arguments()
{
    return "format_usage_required_arguments";
}

std::string printer::format_usage_optional_arguments()
{
    return "format_usage_optional_arguments";
}

std::string printer::format_usage_multivalued_arguments()
{
    return "format_usage_multivalue_arguments";
}

/* Initialization */

// 100% component tested.
static void enqueue_name(int count, std::string& name, argument_list& names)
{
    if (count <= 0)
        return;

    if (count > printer::max_arguments)
        count = -1;

    names.push_back(argument_pair(name, count));
}

// 100% component tested.
// This method just gives us a copy of arguments_metadata private state.
// It would be nice if instead that state was public.
void printer::generate_argument_names()
{
    // Member values
    const auto& arguments = get_arguments();
    auto& argument_names = get_argument_names();

    argument_names.clear();
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

        // This is a duplicate of the previous name, so increment the count.
        if (argument_name == previous_argument_name)
        {
            ++max_previous_argument;
            continue;
        }

        enqueue_name(max_previous_argument, previous_argument_name,
            argument_names);
        previous_argument_name = argument_name;
        max_previous_argument = 1;
    }

    // Save the previous name (if there is one).
    enqueue_name(max_previous_argument, previous_argument_name,
        argument_names);
}

// 100% component tested.
void printer::generate_parameters()
{
    const auto& argument_names = get_argument_names();
    const auto& options = get_options();
    auto& parameters = get_parameters();

    parameters.clear();

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

void printer::print(std::ostream& output)
{
    output
        << format_usage()
        << format_description()
        << BX_PRINTER_OPTION_TABLE_HEADER
        << format_parameters_table(false)
        << BX_PRINTER_ARGUMENT_TABLE_HEADER
        << format_parameters_table(true);
}