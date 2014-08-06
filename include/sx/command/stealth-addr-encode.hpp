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
#ifndef SX_STEALTH_ADDR_ENCODE_HPP
#define SX_STEALTH_ADDR_ENCODE_HPP

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
#include <sx/serializer/btc160.hpp>
#include <sx/serializer/btc256.hpp>
#include <sx/serializer/byte.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/ec_public.hpp>
#include <sx/serializer/hd_key.hpp>
#include <sx/serializer/hd_private.hpp>
#include <sx/serializer/hd_public.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/serializer/input.hpp>
#include <sx/serializer/item.hpp>
#include <sx/serializer/output.hpp>
#include <sx/serializer/prefix.hpp>
#include <sx/serializer/raw.hpp>
#include <sx/serializer/script.hpp>
#include <sx/serializer/wif.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extension {

/**
 * Class to implement the sx stealth-addr-encode command.
 */
class stealth_addr_encode 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "stealth-addr-encode"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return stealth_addr_encode::symbol();
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
     *
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("SCAN_KEY", 1)
            .add("SPEND_KEY", -1);
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
        load_input(get_spend_keys_argument(), "SPEND_KEY", variables, input);
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
                "Encode a stealth address."
            )
            (
                "prefix,p",
                value<serializer::prefix>(&option_.prefix),
                "The binary encoded stealth search prefix."
            )
            (
                "reuse-key,r",
                value<bool>(&option_.reuse_key)->implicit_value(true),
                "Reuse the SCAN_PUBKEY as a SPEND_PUBKEY."
            )
            (
                "signatures,s",
                value<serializer::byte>(&option_.signatures),
                "Specify the number of signatures needed. Defaults to the number of SPEND_PUBKEYs provided."
            )
            (
                "SCAN_KEY",
                value<serializer::ec_public>(&argument_.scan_key)->required(),
                "The hex encoded EC public key of the recipient."
            )
            (
                "SPEND_KEY",
                value<std::vector<serializer::ec_public>>(&argument_.spend_keys),
                "The set of hex encoded EC public keys that are spent to."
            );

        return options;
    }

    /**
     * Invoke the command.
     *
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke(std::ostream& output, std::ostream& cerr);
        
    /* Properties */

    /**
     * Get the value of the SCAN_KEY argument.
     */
    virtual serializer::ec_public& get_scan_key_argument()
    {
        return argument_.scan_key;
    }
    
    /**
     * Set the value of the SCAN_KEY argument.
     */
    virtual void set_scan_key_argument(
        const serializer::ec_public& value)
    {
        argument_.scan_key = value;
    }

    /**
     * Get the value of the SPEND_KEY arguments.
     */
    virtual std::vector<serializer::ec_public>& get_spend_keys_argument()
    {
        return argument_.spend_keys;
    }
    
    /**
     * Set the value of the SPEND_KEY arguments.
     */
    virtual void set_spend_keys_argument(
        const std::vector<serializer::ec_public>& value)
    {
        argument_.spend_keys = value;
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
     * Get the value of the prefix option.
     */
    virtual serializer::prefix& get_prefix_option()
    {
        return option_.prefix;
    }
    
    /**
     * Set the value of the prefix option.
     */
    virtual void set_prefix_option(
        const serializer::prefix& value)
    {
        option_.prefix = value;
    }

    /**
     * Get the value of the reuse-key option.
     */
    virtual bool& get_reuse_key_option()
    {
        return option_.reuse_key;
    }
    
    /**
     * Set the value of the reuse-key option.
     */
    virtual void set_reuse_key_option(
        const bool& value)
    {
        option_.reuse_key = value;
    }

    /**
     * Get the value of the signatures option.
     */
    virtual serializer::byte& get_signatures_option()
    {
        return option_.signatures;
    }
    
    /**
     * Set the value of the signatures option.
     */
    virtual void set_signatures_option(
        const serializer::byte& value)
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
          : scan_key(),
            spend_keys()
        {
        }
        
        serializer::ec_public scan_key;
        std::vector<serializer::ec_public> spend_keys;
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
            prefix(),
            reuse_key(),
            signatures()
        {
        }
        
        bool help;
        serializer::prefix prefix;
        bool reuse_key;
        serializer::byte signatures;
    } option_;
};

} // extension
} // sx

#endif
