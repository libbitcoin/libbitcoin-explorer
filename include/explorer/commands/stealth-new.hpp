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
#ifndef BX_STEALTH_NEW_HPP
#define BX_STEALTH_NEW_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/command.hpp>
#include <explorer/define.hpp>
#include <explorer/generated.hpp>
#include <explorer/primitives/address.hpp>
#include <explorer/primitives/base16.hpp>
#include <explorer/primitives/base58.hpp>
#include <explorer/primitives/btc.hpp>
#include <explorer/primitives/btc160.hpp>
#include <explorer/primitives/btc256.hpp>
#include <explorer/primitives/ec_private.hpp>
#include <explorer/primitives/ec_public.hpp>
#include <explorer/primitives/encoding.hpp>
#include <explorer/primitives/hashtype.hpp>
#include <explorer/primitives/hd_key.hpp>
#include <explorer/primitives/hd_priv.hpp>
#include <explorer/primitives/hd_pub.hpp>
#include <explorer/primitives/header.hpp>
#include <explorer/primitives/input.hpp>
#include <explorer/primitives/output.hpp>
#include <explorer/primitives/prefix.hpp>
#include <explorer/primitives/raw.hpp>
#include <explorer/primitives/script.hpp>
#include <explorer/primitives/stealth.hpp>
#include <explorer/primitives/transaction.hpp>
#include <explorer/primitives/wif.hpp>
#include <explorer/primitives/wrapper.hpp>
#include <explorer/utility/compat.hpp>
#include <explorer/utility/config.hpp>
#include <explorer/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace explorer {
namespace commands {

/**
 * Class to implement the stealth-new command.
 */
class stealth_new 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "stealth-new"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return stealth_new::symbol();
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
            .add("EPHEMERAL_SECRET", 1)
            .add("SCAN_PUBKEY", 1)
            .add("SPEND_PUBKEY", 1);
    }
	
	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
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
                BX_VARIABLE_CONFIG ",c",
                value<boost::filesystem::path>(),                 
                "The path and file name for the configuration settings file for this application."
            )
            (
                "help,h",
                value<bool>(&option_.help)->implicit_value(true),
                "Create a new stealth public key from which a payment address can be generated. A unique ephemeral secret should be used for each stealth payment."
            )
            (
                "EPHEMERAL_SECRET",
                value<primitives::ec_private>(&argument_.ephemeral_secret),
                "The Base16 ephemeral EC private key used to generate stealth payment metadata."
            )
            (
                "SCAN_PUBKEY",
                value<primitives::ec_public>(&argument_.scan_pubkey),
                "The Base16 EC public key required to generate a stealth address."
            )
            (
                "SPEND_PUBKEY",
                value<primitives::ec_public>(&argument_.spend_pubkey)->required(),
                "A Base16 EC public key corresponding to a private key that can spend payments to the stealth address."
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
     * Get the value of the EPHEMERAL_SECRET argument.
     */
    virtual primitives::ec_private& get_ephemeral_secret_argument()
    {
        return argument_.ephemeral_secret;
    }
    
    /**
     * Set the value of the EPHEMERAL_SECRET argument.
     */
    virtual void set_ephemeral_secret_argument(
        const primitives::ec_private& value)
    {
        argument_.ephemeral_secret = value;
    }

    /**
     * Get the value of the SCAN_PUBKEY argument.
     */
    virtual primitives::ec_public& get_scan_pubkey_argument()
    {
        return argument_.scan_pubkey;
    }
    
    /**
     * Set the value of the SCAN_PUBKEY argument.
     */
    virtual void set_scan_pubkey_argument(
        const primitives::ec_public& value)
    {
        argument_.scan_pubkey = value;
    }

    /**
     * Get the value of the SPEND_PUBKEY argument.
     */
    virtual primitives::ec_public& get_spend_pubkey_argument()
    {
        return argument_.spend_pubkey;
    }
    
    /**
     * Set the value of the SPEND_PUBKEY argument.
     */
    virtual void set_spend_pubkey_argument(
        const primitives::ec_public& value)
    {
        argument_.spend_pubkey = value;
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
          : ephemeral_secret(),
            scan_pubkey(),
            spend_pubkey()
        {
        }
        
        primitives::ec_private ephemeral_secret;
        primitives::ec_public scan_pubkey;
        primitives::ec_public spend_pubkey;
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

} // commands
} // explorer

#endif
