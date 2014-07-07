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
#ifndef SX_SHOWBLKHEAD_HPP
#define SX_SHOWBLKHEAD_HPP

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <sx/command.hpp>
#include <sx/define.hpp>
#include <sx/generated.hpp>
#include <sx/serializer/byte.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/serializer/secret.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extension {

/**
 * Class to implement the sx showblkhead command.
 */
class showblkhead 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "showblkhead"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    const char* name()
    {
        return showblkhead::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    const char* category()
    {
        return "OFFLINE BLOCKCHAIN";
    }

    /**
     * The localizable command subcategory name, upper case.
     */
    const char* subcategory()
    {
        return "HEADERS";
    }

    /**
     * DEPRECATED
     * The localizable command description, multiple lines, punctuated.
     */
    const std::vector<const char*> description()
    {
        return
        {
            { "Show the details of a block header." },
        };
    }

    /**
     * DEPRECATED
     * The non-localizable command usage examples, multiple lines.
     */
    const std::vector<const char*> example()
    {
        return
        {
            { "sx showblkhead [FILENAME]" },
        };
    }

    /**
     * DEPRECATED
     * The localizable command explanation, multiple lines, punctuated.
     */
    const std::vector<const char*> explanation()
    {
        return
        {
            { "'showblkhead' allows inspecting of block headers." }
            { "" }
            { "  $ sx showblkhead headerfile.blk" }
            { "  hash: 4d25b18ed094ad68f75f21692d8540f45ceb90b240a521b8f191e95d8b6b8bb0" }
            { "  version: 1  locktime: 0" }
            { "  Input:" }
            { "    previous output:" }
            { "  97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0" }
            { "    script:   sequence: 4294967295" }
            { "  Output:" }
            { "    value: 90000" }
            { "    script: dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify" }
            { "  checksig" }
            { "    address: 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe" },
        };
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     *
     * @return  The loaded program argument definitions.
     */
    arguments_metadata& load_arguments()
    {
        return get_argument_metadata();
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
    options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
            (
                SX_VARIABLE_CONFIG ",c",
                value<boost::filesystem::path>(),                 
                ""
            )

        return options;
    }
	
	/**
     * Load streamed value as parameter fallback.
     *
     * @param[in]  input  The input stream for loading the parameter.
     * @param[in]         The loaded variables.
     */
    void load_stream(std::istream& input,
        boost::program_options::variables_map& variables)
    {
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

private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
            {}
    } argument_;
    
    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
            {}    
    } option_;
};

} // extension
} // sx

#endif
