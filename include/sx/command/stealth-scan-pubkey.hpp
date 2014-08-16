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
#ifndef SX_STEALTH_SCAN_PUBKEY_HPP
#define SX_STEALTH_SCAN_PUBKEY_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/command.hpp>
#include <sx/define.hpp>
#include <sx/generated.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/base16.hpp>
#include <sx/serializer/base58.hpp>
#include <sx/serializer/btc.hpp>
#include <sx/serializer/btc160.hpp>
#include <sx/serializer/btc256.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/ec_public.hpp>
#include <sx/serializer/encoding.hpp>
#include <sx/serializer/hashtype.hpp>
#include <sx/serializer/hd_key.hpp>
#include <sx/serializer/hd_priv.hpp>
#include <sx/serializer/hd_pub.hpp>
#include <sx/serializer/header.hpp>
#include <sx/serializer/input.hpp>
#include <sx/serializer/output.hpp>
#include <sx/serializer/prefix.hpp>
#include <sx/serializer/raw.hpp>
#include <sx/serializer/script.hpp>
#include <sx/serializer/stealth.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/serializer/wif.hpp>
#include <sx/serializer/wrapper.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extension {

/**
 * Class to implement the sx stealth-scan-pubkey command.
 */
class stealth_scan_pubkey 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "stealth-scan-pubkey"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return stealth_scan_pubkey::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "STEALTH";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("SCAN_SECRET", 1)
            .add("SPEND_PUBKEY", 1)
            .add("EPHEMERAL_PUBKEY", 1);
    }
	
	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        load_input(get_ephemeral_pubkey_argument(), "EPHEMERAL_PUBKEY", variables, input);
    }
    
    /**
     * Load program option definitions.
     * The implicit_value call allows flags to be strongly-typed on read while
     * allowing but not requiring a value on the command line for the option.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
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
                "Using stealth payment metadata uncover the scan public key (necessary to identify a payment)."
            )
            (
                "SCAN_SECRET",
                value<serializer::ec_private>(&argument_.scan_secret)->required(),
                "The Base16 EC private key corresponding to the public key required to generate a stealth payment."
            )
            (
                "SPEND_PUBKEY",
                value<serializer::ec_public>(&argument_.spend_pubkey)->required(),
                "A Base16 EC public key corresponding to a private key that can spend payments to the stealth address."
            )
            (
                "EPHEMERAL_PUBKEY",
                value<serializer::ec_public>(&argument_.ephemeral_pubkey),
                "The Base16 ephemeral EC public key retrieved from the stealth payment metadata."
            );

        return options;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke(std::ostream& output, std::ostream& cerr);
        
    /* Properties */

    /**
     * Get the value of the SCAN_SECRET argument.
     */
    virtual serializer::ec_private& get_scan_secret_argument()
    {
        return argument_.scan_secret;
    }
    
    /**
     * Set the value of the SCAN_SECRET argument.
     */
    virtual void set_scan_secret_argument(
        const serializer::ec_private& value)
    {
        argument_.scan_secret = value;
    }

    /**
     * Get the value of the SPEND_PUBKEY argument.
     */
    virtual serializer::ec_public& get_spend_pubkey_argument()
    {
        return argument_.spend_pubkey;
    }
    
    /**
     * Set the value of the SPEND_PUBKEY argument.
     */
    virtual void set_spend_pubkey_argument(
        const serializer::ec_public& value)
    {
        argument_.spend_pubkey = value;
    }

    /**
     * Get the value of the EPHEMERAL_PUBKEY argument.
     */
    virtual serializer::ec_public& get_ephemeral_pubkey_argument()
    {
        return argument_.ephemeral_pubkey;
    }
    
    /**
     * Set the value of the EPHEMERAL_PUBKEY argument.
     */
    virtual void set_ephemeral_pubkey_argument(
        const serializer::ec_public& value)
    {
        argument_.ephemeral_pubkey = value;
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

private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
          : scan_secret(),
            spend_pubkey(),
            ephemeral_pubkey()
        {
        }
        
        serializer::ec_private scan_secret;
        serializer::ec_public spend_pubkey;
        serializer::ec_public ephemeral_pubkey;
    } argument_;
    
    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : help()
        {
        }
        
        bool help;
    } option_;
};

} // extension
} // sx

#endif
