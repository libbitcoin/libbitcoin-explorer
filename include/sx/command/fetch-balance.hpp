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
#ifndef SX_FETCH_BALANCE_HPP
#define SX_FETCH_BALANCE_HPP

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/command.hpp>
#include <sx/define.hpp>
#include <sx/generated.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/base58.hpp>
#include <sx/serializer/binary.hpp>
#include <sx/serializer/btc160.hpp>
#include <sx/serializer/btc256.hpp>
#include <sx/serializer/byte.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/ec_public.hpp>
#include <sx/serializer/hd_key.hpp>
#include <sx/serializer/hd_private.hpp>
#include <sx/serializer/hd_public.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/serializer/item.hpp>
#include <sx/serializer/point.hpp>
#include <sx/serializer/raw.hpp>
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
#define SX_FETCH_BALANCE_OUTPUT \
    "Address: %1%\n  Paid balance:    %2%\n  Pending balance: %3%\n  Total received:  %4%"

/**
 * Class to implement the sx fetch-balance command.
 */
class fetch_balance 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "fetch-balance"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return fetch_balance::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "ONLINE";
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
            .add("ADDRESS", -1);
    }
	
	/**
     * Load parameter fallbacks from file or input as appropriate.
     *
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        load_input(get_addresss_argument(), "ADDRESS", variables, input);
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
                "Get the balance in satoshi of one or more Bitcoin addresses. Requires an Obelisk server connection."
            )
            (
                "json,j",
                value<bool>(&option_.json)->implicit_value(true),
                "Enable JSON output."
            )
            (
                "ADDRESS",
                value<std::vector<serializer::address>>(&argument_.addresss),
                "The set of Bitcoin addresses."
            );

        return options;
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
     * Get the value of the ADDRESS arguments.
     */
    virtual std::vector<serializer::address>& get_addresss_argument()
    {
        return argument_.addresss;
    }
    
    /**
     * Set the value of the ADDRESS arguments.
     */
    virtual void set_addresss_argument(
        const std::vector<serializer::address>& value)
    {
        argument_.addresss = value;
    }

    /**
     * Get the value of the help option.
     */
    virtual bool& get_help_option()
    {
        return option_.help;
    }
    
    /**
     * Set the value of the help option.
     */
    virtual void set_help_option(
        const bool& value)
    {
        option_.help = value;
    }

    /**
     * Get the value of the json option.
     */
    virtual bool& get_json_option()
    {
        return option_.json;
    }
    
    /**
     * Set the value of the json option.
     */
    virtual void set_json_option(
        const bool& value)
    {
        option_.json = value;
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
          : addresss()
        {
        }
        
        std::vector<serializer::address> addresss;
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
            json()
        {
        }
        
        bool help;
        bool json;
    } option_;
};

} // extension
} // sx

#endif
