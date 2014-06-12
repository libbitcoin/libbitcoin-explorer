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
#ifndef SX_STEALTH_ADDR_HPP
#define SX_STEALTH_ADDR_HPP

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <sx/command.hpp>
#include <sx/generated.hpp>
#include <sx/utility/byte.hpp>
#include <sx/utility/bytes.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extensions {

/**
 * Class to implement the sx stealth-addr command.
 */
class stealth_addr 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "stealth-addr"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    const char* name()
    {
        return stealth_addr::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    const char* category()
    {
        return "OFFLINE KEYS AND ADDRESSES";
    }

    /**
     * The localizable command subcategory name, upper case.
     */
    const char* subcategory()
    {
        return "STEALTH";
    }

    /**
     * DEPRECATED
     * The localizable command description, multiple lines, punctuated.
     */
    const std::vector<const char*> description()
    {
        return
        {
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
        };
    }
    
    /**
     * Write the usage help for this command to the specified stream.
     *
     * @param[out] stream  The stream of interest.
     */
    void write_usage(std::ostream& stream)
    {
        stream << "foobar" << std::endl;
    }
    
    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     *
     * @param[out] definitions  The defined program argument definitions.
     */
    void load_arguments(
        boost::program_options::positional_options_description& definitions)
    {
        definitions.add("SCAN_PUBKEY", 1);
        definitions.add("SPEND_PUBKEY", -1);
    }
    
    /**
     * Load program option definitions.
     * The implicit_value call allows flags to be strongly-typed on read while
     * allowing but not requiring a value on the command line for the option.
     *
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     *
     * @param[out] definitions  The defined program option definitions.
     */
    void load_options(
        boost::program_options::options_description& definitions)
    {
        using namespace boost::program_options;
        definitions.add_options()
            (
                SX_VARIABLE_CONFIG ",c",
                value<boost::filesystem::path>(),                 
                "The path and file name for the configuration settings file for this application."
            )
            (
                "help,h",
                value<bool>(&option_.help)->implicit_value(true),
                "Generate a stealth address from given input."
            )
            (
                "reuse-key,r",
                value<bool>(&option_.reuse_key)->implicit_value(true),
                "Reuse the SCAN_PUBKEY as a SPEND_PUBKEY."
            )
            (
                "signatures,s",
                value<sx::byte>(&option_.signatures),
                "Specify the number of signatures needed. Defaults to the number of SPEND_PUBKEYs provided."
            )
            (
                "SCAN_PUBKEY",
                value<bytes>(&argument_.scan_pubkey)->required(),
                "The public key of the recipient."
            )
            (
                "SPEND_PUBKEY",
                value<std::vector<bytes>>(&argument_.spend_pubkeys),
                "The public key that is spent to."
            );
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
     * Get the value of the SCAN_PUBKEY argument.
     */
    virtual bytes get_scan_pubkey_argument()
    {
        return argument_.scan_pubkey;
    }
    
    /**
     * Set the value of the SCAN_PUBKEY argument.
     */
    virtual void set_scan_pubkey_argument(bytes value)
    {
        argument_.scan_pubkey = value;
    }

    /**
     * Get the value of the SPEND_PUBKEY arguments.
     */
    virtual std::vector<bytes> get_spend_pubkeys_argument()
    {
        return argument_.spend_pubkeys;
    }
    
    /**
     * Set the value of the SPEND_PUBKEY arguments.
     */
    virtual void set_spend_pubkeys_argument(std::vector<bytes> value)
    {
        argument_.spend_pubkeys = value;
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
     * Get the value of the reuse-key option.
     */
    virtual bool get_reuse_key_option()
    {
        return option_.reuse_key;
    }
    
    /**
     * Set the value of the reuse-key option.
     */
    virtual void set_reuse_key_option(bool value)
    {
        option_.reuse_key = value;
    }

    /**
     * Get the value of the signatures option.
     */
    virtual sx::byte get_signatures_option()
    {
        return option_.signatures;
    }
    
    /**
     * Set the value of the signatures option.
     */
    virtual void set_signatures_option(sx::byte value)
    {
        option_.signatures = value;
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
            {}
        bytes scan_pubkey;
        std::vector<bytes> spend_pubkeys;
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
            reuse_key(),
            signatures()
            {}    
        bool help;
        bool reuse_key;
        sx::byte signatures;
    } option_;
};

} // extensions
} // sx

#endif
