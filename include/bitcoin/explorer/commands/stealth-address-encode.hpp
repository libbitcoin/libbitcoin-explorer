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
#ifndef BX_STEALTH_ADDRESS_ENCODE_HPP
#define BX_STEALTH_ADDRESS_ENCODE_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/generated.hpp>
#include <bitcoin/explorer/primitives/address.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/base2.hpp>
#include <bitcoin/explorer/primitives/base58.hpp>
#include <bitcoin/explorer/primitives/btc.hpp>
#include <bitcoin/explorer/primitives/btc160.hpp>
#include <bitcoin/explorer/primitives/btc256.hpp>
#include <bitcoin/explorer/primitives/ec_private.hpp>
#include <bitcoin/explorer/primitives/ec_public.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/hashtype.hpp>
#include <bitcoin/explorer/primitives/hd_key.hpp>
#include <bitcoin/explorer/primitives/hd_priv.hpp>
#include <bitcoin/explorer/primitives/hd_pub.hpp>
#include <bitcoin/explorer/primitives/header.hpp>
#include <bitcoin/explorer/primitives/input.hpp>
#include <bitcoin/explorer/primitives/output.hpp>
#include <bitcoin/explorer/primitives/raw.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/primitives/stealth.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/primitives/wif.hpp>
#include <bitcoin/explorer/primitives/wrapper.hpp>
#include <bitcoin/explorer/utility/compat.hpp>
#include <bitcoin/explorer/utility/config.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_STEALTH_ADDRESS_ENCODE_PREFIX_TOO_LONG \
    "The prefix is limited to 32 bits."
#define BX_STEALTH_ADDRESS_ENCODE_SIGNATURES_OVERFLOW \
    "The number of signatures is greater than the number of SPEND_PUBKEYs."
#define BX_STEALTH_ADDRESS_ENCODE_PREFIX_NOT_SUPPORTED \
    "WARNING: prefix search is not yet fully supported."
#define BX_STEALTH_ADDRESS_ENCODE_MULTISIG_NOT_SUPPORTED \
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
                BX_VARIABLE_CONFIG ",c",
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
                value<primitives::base2>(&option_.prefix),
                "The Base2 stealth prefix that will be used to locate payments."
            )
            (
                "signatures,s",
                value<uint8_t>(&option_.signatures),
                "Specify the number of signatures required to spend a payment to the stealth address. Defaults to the number of SPEND_PUBKEYs."
            )
            (
                "SCAN_PUBKEY",
                value<primitives::ec_public>(&argument_.scan_pubkey)->required(),
                "The Base16 EC public key required to generate a payment."
            )
            (
                "SPEND_PUBKEY",
                value<std::vector<primitives::ec_public>>(&argument_.spend_pubkeys),
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
     * Get the value of the SPEND_PUBKEY arguments.
     */
    virtual std::vector<primitives::ec_public>& get_spend_pubkeys_argument()
    {
        return argument_.spend_pubkeys;
    }
    
    /**
     * Set the value of the SPEND_PUBKEY arguments.
     */
    virtual void set_spend_pubkeys_argument(
        const std::vector<primitives::ec_public>& value)
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
    virtual primitives::base2& get_prefix_option()
    {
        return option_.prefix;
    }
    
    /**
     * Set the value of the prefix option.
     */
    virtual void set_prefix_option(
        const primitives::base2& value)
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
        
        primitives::ec_public scan_pubkey;
        std::vector<primitives::ec_public> spend_pubkeys;
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
        primitives::base2 prefix;
        uint8_t signatures;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
