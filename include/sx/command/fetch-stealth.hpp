/**
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
#ifndef SX_FETCH_STEALTH_HPP
#define SX_FETCH_STEALTH_HPP

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <sx/command.hpp>
#include <sx/define.hpp>
#include <sx/generated.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/base58.hpp>
#include <sx/serializer/bitcoin160.hpp>
#include <sx/serializer/bitcoin256.hpp>
#include <sx/serializer/byte.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/ec_public.hpp>
#include <sx/serializer/hd_key.hpp>
#include <sx/serializer/hd_private.hpp>
#include <sx/serializer/hd_public.hpp>
#include <sx/serializer/point.hpp>
#include <sx/serializer/wif.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extension {

/**
 * Various localizable strings.
 */
#define SX_FETCH_STEALTH_OUTPUT \
    "Ephemeral key: %1% Address: %2% Transaction hash: %3%\n"

/**
 * Class to implement the sx fetch-stealth command.
 */
class fetch_stealth 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "fetch-stealth"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    const char* name()
    {
        return fetch_stealth::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    const char* category()
    {
        return "OBELISK";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     *
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("PREFIX", 1);
    }
    
    /**
     * Load program option definitions.
     * The implicit_value call allows flags to be strongly-typed on read while
     * allowing but not requiring a value on the command line for the option.
     *
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     *
     * @return  The loaded program option definitions.
     */
    virtual options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
            (
                SX_VARIABLE_CONFIG ",c",
                value<boost::filesystem::path>(),                 
                "The path and file name for the configuration settings file for this application."
            )
            (
                "help,h",
                value<bool>(&option_.help)->implicit_value(true),
                "Get the stealth transactions matching the specified filter. Requires a server connection."
            )
            (
                "height,t",
                value<size_t>(&option_.height),
                "The minimum height of transactions to include in the search."
            )
            (
                "PREFIX",
                value<uint32_t>(&argument_.prefix),
                "The prefix of transactions to include in the search."
            );

        return options;
    }
	
	/**
     * Load streamed value as parameter fallback.
     *
     * @param[in]  input  The input stream for loading the parameter.
     * @param[in]         The loaded variables.
     */
    virtual void load_stream(std::istream& input, po::variables_map& variables)
    {
        auto prefix = variables.find("PREFIX");
        if (prefix == variables.end())
            parse(argument_.prefix, read_stream(input));
    }

    /**
     * Invoke the command.
     *
     * @param[in]   input   The input stream for the command execution.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke(std::istream& input, std::ostream& output,
        std::ostream& cerr);
        
    /* Properties */

    /**
     * Get the value of the PREFIX argument.
     */
    virtual uint32_t get_prefix_argument()
    {
        return argument_.prefix;
    }
    
    /**
     * Set the value of the PREFIX argument.
     */
    virtual void set_prefix_argument(uint32_t value)
    {
        argument_.prefix = value;
    }

    /**
     * Get the value of the help option.
     */
    virtual bool get_help_option()
    {
        return option_.help;
    }
    
    /**
     * Set the value of the help option.
     */
    virtual void set_help_option(bool value)
    {
        option_.help = value;
    }

    /**
     * Get the value of the height option.
     */
    virtual size_t get_height_option()
    {
        return option_.height;
    }
    
    /**
     * Set the value of the height option.
     */
    virtual void set_height_option(size_t value)
    {
        option_.height = value;
    }

private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
          : prefix()
            {}
        uint32_t prefix;
    } argument_;
    
    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : help(),
            height()
            {}    
        bool help;
        size_t height;
    } option_;
};

} // extension
} // sx

#endif
