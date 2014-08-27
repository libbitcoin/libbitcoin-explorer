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
#ifndef SX_STEALTH_ADDRESS_ENCODE_HPP
#define SX_STEALTH_ADDRESS_ENCODE_HPP

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

namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define SX_STEALTH_ADDRESS_ENCODE_SIGNATURES_OVERFLOW \
    "The number of signatures is greater than the number of SPEND_PUBKEYs."
#define SX_STEALTH_ADDRESS_ENCODE_PREFIX_NOT_SUPPORTED \
    "WARNING: prefix search is not yet fully supported."
#define SX_STEALTH_ADDRESS_ENCODE_MULTISIG_NOT_SUPPORTED \
    "WARNING: multiple signature stealth transactions are not yet fully supported."

/**
 * Class to implement the stealth-address-encode command.
 */
class stealth_address_encode 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "stealth-address-encode"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return stealth_address_encode::symbol();
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
            .add("SCAN_PUBKEY", 1)
            .add("SPEND_PUBKEY", -1);
    }
	
	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        //load_input(get_spend_pubkeys_argument(), "SPEND_PUBKEY", variables, input);
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
                "Encode a stealth payment address."
            )
            (
                "prefix,p",
                value<serializer::prefix>(&option_.prefix),
                "The Base2 stealth prefix that will be used to locate payments."
            )
            (
                "signatures,s",
                value<uint8_t>(&option_.signatures),
                "Specify the number of signatures required to spend a payment to the stealth address. Defaults to the number of SPEND_PUBKEYs."
            )
            (
                "SCAN_PUBKEY",
                value<serializer::ec_public>(&argument_.scan_pubkey)->required(),
                "The Base16 EC public key required to generate a payment."
            )
            (
                "SPEND_PUBKEY",
                value<std::vector<serializer::ec_public>>(&argument_.spend_pubkeys),
                "The set of Base16 EC public keys corresponding to private keys that will be able to spend payments to the address. Defaults to the value of SCAN_EC_PUBLIC_KEY."
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
     * Get the value of the SCAN_PUBKEY argument.
     */
    virtual serializer::ec_public& get_scan_pubkey_argument()
    {
        return argument_.scan_pubkey;
    }
    
    /**
     * Set the value of the SCAN_PUBKEY argument.
     */
    virtual void set_scan_pubkey_argument(
        const serializer::ec_public& value)
    {
        argument_.scan_pubkey = value;
    }

    /**
     * Get the value of the SPEND_PUBKEY arguments.
     */
    virtual std::vector<serializer::ec_public>& get_spend_pubkeys_argument()
    {
        return argument_.spend_pubkeys;
    }
    
    /**
     * Set the value of the SPEND_PUBKEY arguments.
     */
    virtual void set_spend_pubkeys_argument(
        const std::vector<serializer::ec_public>& value)
    {
        argument_.spend_pubkeys = value;
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
     * Get the value of the signatures option.
     */
    virtual uint8_t& get_signatures_option()
    {
        return option_.signatures;
    }
    
    /**
     * Set the value of the signatures option.
     */
    virtual void set_signatures_option(
        const uint8_t& value)
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
          : scan_pubkey(),
            spend_pubkeys()
        {
        }
        
        serializer::ec_public scan_pubkey;
        std::vector<serializer::ec_public> spend_pubkeys;
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
            signatures()
        {
        }
        
        bool help;
        serializer::prefix prefix;
        uint8_t signatures;
    } option_;
};

} // commands
} // explorer

#endif
