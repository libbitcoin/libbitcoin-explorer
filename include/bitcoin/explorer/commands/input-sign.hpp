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
#ifndef BX_INPUT_SIGN_HPP
#define BX_INPUT_SIGN_HPP

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
#define BX_INPUT_SIGN_SHORT_NONCE \
    "The nonce is less than 128 bits long."
#define BX_INPUT_SIGN_INDEX_OUT_OF_RANGE \
    "The index does not refer to an existing input."
#define BX_INPUT_SIGN_FAILED \
    "The signing operation failed."

/**
 * Class to implement the input-sign command.
 */
class input_sign 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "input-sign"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return input_sign::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "TRANSACTION";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("EC_PRIVATE_KEY", 1)
            .add("NONCE", 1)
            .add("PREVIOUS_OUTPUT_SCRIPT", 1)
            .add("TRANSACTION", 1);
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
                BX_CONFIG_VARIABLE ",c",
                value<boost::filesystem::path>(),
                "The path and file name for the configuration settings file to be used in the execution of the command."
            )
            (
                "help,h",
                value<bool>(&option_.help)->implicit_value(true),
                "Create a signature for a transaction input."
            )
            (
                "index,i",
                value<size_t>(&option_.index),
                "The ordinal position of the input within the transaction, defaults to zero."
            )
            (
                "signature_type,s",
                value<primitives::hashtype>(&option_.signature_type),
                "A token that indicates how the transaction should be hashed for signing. Options are 'all', 'none', 'single', or 'anyone_can_pay', defaults to 'single'."
            )
            (
                "EC_PRIVATE_KEY",
                value<primitives::ec_private>(&argument_.ec_private_key)->required(),
                "The Base16 EC private key to sign with."
            )
            (
                "NONCE",
                value<primitives::base16>(&argument_.nonce)->required(),
                "The Base16 random value to be used as the signing nonce. Must be at least 128 bits in length."
            )
            (
                "PREVIOUS_OUTPUT_SCRIPT",
                value<primitives::script>(&argument_.previous_output_script),
                "The previous output script to use in signing."
            )
            (
                "TRANSACTION",
                value<primitives::transaction>(&argument_.transaction)->required(),
                "The Base16 transaction. If not specified the transaction is read from STDIN."
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
     * Get the value of the EC_PRIVATE_KEY argument.
     */
    virtual primitives::ec_private& get_ec_private_key_argument()
    {
        return argument_.ec_private_key;
    }
    
    /**
     * Set the value of the EC_PRIVATE_KEY argument.
     */
    virtual void set_ec_private_key_argument(
        const primitives::ec_private& value)
    {
        argument_.ec_private_key = value;
    }

    /**
     * Get the value of the NONCE argument.
     */
    virtual primitives::base16& get_nonce_argument()
    {
        return argument_.nonce;
    }
    
    /**
     * Set the value of the NONCE argument.
     */
    virtual void set_nonce_argument(
        const primitives::base16& value)
    {
        argument_.nonce = value;
    }

    /**
     * Get the value of the PREVIOUS_OUTPUT_SCRIPT argument.
     */
    virtual primitives::script& get_previous_output_script_argument()
    {
        return argument_.previous_output_script;
    }
    
    /**
     * Set the value of the PREVIOUS_OUTPUT_SCRIPT argument.
     */
    virtual void set_previous_output_script_argument(
        const primitives::script& value)
    {
        argument_.previous_output_script = value;
    }

    /**
     * Get the value of the TRANSACTION argument.
     */
    virtual primitives::transaction& get_transaction_argument()
    {
        return argument_.transaction;
    }
    
    /**
     * Set the value of the TRANSACTION argument.
     */
    virtual void set_transaction_argument(
        const primitives::transaction& value)
    {
        argument_.transaction = value;
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
     * Get the value of the index option.
     */
    virtual size_t& get_index_option()
    {
        return option_.index;
    }
    
    /**
     * Set the value of the index option.
     */
    virtual void set_index_option(
        const size_t& value)
    {
        option_.index = value;
    }

    /**
     * Get the value of the signature_type option.
     */
    virtual primitives::hashtype& get_signature_type_option()
    {
        return option_.signature_type;
    }
    
    /**
     * Set the value of the signature_type option.
     */
    virtual void set_signature_type_option(
        const primitives::hashtype& value)
    {
        option_.signature_type = value;
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
          : ec_private_key(),
            nonce(),
            previous_output_script(),
            transaction()
        {
        }
        
        primitives::ec_private ec_private_key;
        primitives::base16 nonce;
        primitives::script previous_output_script;
        primitives::transaction transaction;
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
            index(),
            signature_type()
        {
        }
        
        bool help;
        size_t index;
        primitives::hashtype signature_type;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
