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
#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/explorer/utility/parameter.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
    
/**
 * Class for managing the serialization of command line options and arguments.
 */
class printer
{
public:
        
    /**
     * Number of arguments above which the argument is considered unlimited.
     */
    static const int max_arguments = 256;

    /*
     * Construct an instance of the printer class.
     * @param[in]  application  This application (e.g. 'bx').
     * @param[in]  command      This application (e.g. 'btc').
     * @param[in]  arguments    Populated command line arguments metadata.
     * @param[in]  options      Populated command line options metadata.
     */
    printer(const std::string& application, const std::string& command,
        const arguments_metadata& arguments, const options_metadata& options);

    /**
     * Convert a paragraph of text into a column.
     * This formats to 80 char width as: [ 23 | ' ' | 55 | '\n' ].
     * If one word exceeds width it will cause a column overflow.
     * This always sets at least one line and always collapses whitespace.
     * @param[in]  paragraph  The paragraph to columnize.
     * @return                The column, as a list of fragments.
     */
    virtual std::vector<std::string> columnize(const std::string& paragraph,
        size_t width);
    
    /**
     * Format the parameters table.
     * @param[in]  positional  True for positional otherwize named.
     * @return                 The formatted help arguments table.
     */
    virtual std::string format_parameters_table(bool positional);

    /**
     * Format the command line usage.
     * @return  The formatted usage.
     */
    virtual std::string format_usage();

    /**
     * Format the command line parameters.
     * @return  The formatted command line parameters.
     */
    virtual std::string format_usage_parameters();

    /**
     * Format the boolean command line options.
     * @return  The formatted command line options.
     */
    virtual std::string format_usage_toggle_options();
    
    /**
     * Format the required command line options.
     * @return  The formatted command line options.
     */
    virtual std::string format_usage_required_options();
    
    /**
     * Format the optional non-boolean command line options.
     * @return  The formatted command line options.
     */
    virtual std::string format_usage_optional_options();
    
    /**
     * Format the multiple-valued command line options.
     * @return  The formatted command line options.
     */
    virtual std::string format_usage_multivalued_options();
    
    /**
     * Format the required command line positional arguments.
     * @return  The formatted command line arguments.
     */
    virtual std::string format_usage_required_arguments();
    
    /**
     * Format the optional command line positional arguments.
     * @return  The formatted command line arguments.
     */
    virtual std::string format_usage_optional_arguments();
    
    /**
     * Format the multiple-valued command line positional arguments.
     * @return  The formatted command line arguments.
     */
    virtual std::string format_usage_multivalued_arguments();
    
    /**
     * Build the list of argument name/count tuples.
     */
    virtual void generate_argument_names();

    /**
     * Build the list of parameters.
     */
    virtual void generate_parameters();

    /**
     * Parse the arguments and options into the normalized parameter list.
     */
    virtual void initialize();

    /**
     * Serialize command line help (full details).
     * @param[out] output  Stream that is sink for print output. 
     */
    virtual void print(std::ostream& output);

    /**
     * Virtual property declarations, passed on construct.
     */
    PROPERTY_GET_REF(std::string, application);
    PROPERTY_GET_REF(std::string, command);
    PROPERTY_GET_REF(arguments_metadata, arguments);
    PROPERTY_GET_REF(options_metadata, options);

    /**
     * Virtual property declarations, generated from metadata.
     */
    PROPERTY_GET_REF(argument_list, argument_names);
    PROPERTY_GET_REF(parameter_list, parameters);
};

} // namespace explorer
} // namespace libbitcoin

#endif