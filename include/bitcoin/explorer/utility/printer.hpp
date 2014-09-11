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
#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/explorer/utility/parameter.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

/*
    USAGE: sx command [-hvt] [-w ARG]... [-m ARG] -n ARG ADD [LIKE]...

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

namespace libbitcoin {
namespace explorer {
    
/**
 * Class for managing the serialization of command line options and arguments.
 */
class printer
{
public:

    /*
     * Construct an instance of the printer class.
     * @param[out] output       Stream that is sink for print output.
     * @param[in]  options      Populated command line options metadata.
     * @param[in]  arguments    Populated command line arguments metadata.
     * @param[in]  application  This application [and command (e.g. 'bx btc')].
     */
    printer(std::ostream& output, options_metadata& options,
        arguments_metadata& arguments, const std::string& application)
        : application_(application), arguments_(arguments), options_(options),
        output_(output)
    {
    }
    
    /**
     * Format the help arguments table.
     * @return  The formatted help arguments table.
     */
    virtual std::string format_help_arguments();

    /**
     * Format the help options table.
     * @return  The formatted help options table.
     */
    virtual std::string format_help_options();

    /**
     * Format the command line usage.
     * @return  The formatted usage.
     */
    virtual std::string format_usage();

    /**
     * Format the command line arguments.
     * @return  The formatted command line arguments.
     */
    virtual std::string format_usage_arguments();

    /**
     * Format the command line options.
     * @return  The formatted command line options.
     */
    virtual std::string format_usage_options();

    /**
     * Format the command line parameters (exclusive of the application).
     * @return  The formatted command line parameters.
     */
    virtual std::string format_usage_parameters();

    /**
     * Format the command line toggle options.
     * @return  The formatted command line toggle options.
     */
    virtual std::string format_usage_toggle_options();

    /**
     * Format the command line value options.
     * @return  The formatted command line value options.
     */
    virtual std::string format_usage_value_options();

    /**
     * Parse the arguments and options into the normalized parameter list.
     */
    virtual void initialize();

    /**
     * Serialize command line help (full details).
     */
    virtual void print_help();

    /**
     * Serialize command line usage (one line example).
     */
    virtual void print_usage();

    /**
     * Virtual property declarations.
     */
    PROPERTY_GET(std::string, application);
    PROPERTY_GET(argument_list, argument_names);
    PROPERTY_GET(arguments_metadata&, arguments);
    PROPERTY_GET(options_metadata&, options);
    PROPERTY_GET(std::ostream&, output);
    PROPERTY_GET(parameter_list, parameters);
};

} // namespace explorer
} // namespace libbitcoin

#endif