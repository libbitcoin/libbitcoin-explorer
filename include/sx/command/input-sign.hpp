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
#ifndef SX_INPUT_SIGN_HPP
#define SX_INPUT_SIGN_HPP

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
 * Various localizable strings.
 */
#define SX_INPUT_SIGN_SHORT_NONCE \
    "The nonce is less than 128 bits long."
#define SX_INPUT_SIGN_INDEX_OUT_OF_RANGE \
    "The index does not refer to an existing input."
#define SX_INPUT_SIGN_FAILED \
    "The signing operation failed."

/**
 * Class to implement the sx input-sign command.
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
            .add("TRANSACTION", 1)
            .add("EC_PRIVATE_KEY", 1)
            .add("NONCE", 1)
            .add("PREVOUT_SCRIPT", 1);
    }
	
	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        load_path(get_transaction_argument(), "TRANSACTION", variables);
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
                "Create a signature for a transaction input."
            )
            (
                "index,i",
                value<size_t>(&option_.index),
                "The ordinal position of the input within the transaction, defaults to zero."
            )
            (
                "sighash,s",
                value<serializer::hashtype>(&option_.sighash),
                "A token that indicates how the transaction should be signed. Options are 'all', 'none', 'single', or 'anyone_can_pay', defaults to 'single'."
            )
            (
                "TRANSACTION",
                value<std::string>()->required(),
                "The file path of the Base16 transaction."
            )
            (
                "EC_PRIVATE_KEY",
                value<serializer::ec_private>(&argument_.ec_private_key)->required(),
                "The Base16 EC private key to sign with."
            )
            (
                "NONCE",
                value<serializer::base16>(&argument_.nonce)->required(),
                "The Base16 random value to be used as the signing nonce. Must be at least 128 bits in length."
            )
            (
                "PREVOUT_SCRIPT",
                value<serializer::script>(&argument_.prevout_script),
                "The Base16 previous output script to use in signing. If not specified the script is read from STDIN."
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
     * Get the value of the TRANSACTION argument.
     */
    virtual serializer::transaction& get_transaction_argument()
    {
        return argument_.transaction;
    }
    
    /**
     * Set the value of the TRANSACTION argument.
     */
    virtual void set_transaction_argument(
        const serializer::transaction& value)
    {
        argument_.transaction = value;
    }

    /**
     * Get the value of the EC_PRIVATE_KEY argument.
     */
    virtual serializer::ec_private& get_ec_private_key_argument()
    {
        return argument_.ec_private_key;
    }
    
    /**
     * Set the value of the EC_PRIVATE_KEY argument.
     */
    virtual void set_ec_private_key_argument(
        const serializer::ec_private& value)
    {
        argument_.ec_private_key = value;
    }

    /**
     * Get the value of the NONCE argument.
     */
    virtual serializer::base16& get_nonce_argument()
    {
        return argument_.nonce;
    }
    
    /**
     * Set the value of the NONCE argument.
     */
    virtual void set_nonce_argument(
        const serializer::base16& value)
    {
        argument_.nonce = value;
    }

    /**
     * Get the value of the PREVOUT_SCRIPT argument.
     */
    virtual serializer::script& get_prevout_script_argument()
    {
        return argument_.prevout_script;
    }
    
    /**
     * Set the value of the PREVOUT_SCRIPT argument.
     */
    virtual void set_prevout_script_argument(
        const serializer::script& value)
    {
        argument_.prevout_script = value;
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
     * Get the value of the sighash option.
     */
    virtual serializer::hashtype& get_sighash_option()
    {
        return option_.sighash;
    }
    
    /**
     * Set the value of the sighash option.
     */
    virtual void set_sighash_option(
        const serializer::hashtype& value)
    {
        option_.sighash = value;
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
          : transaction(),
            ec_private_key(),
            nonce(),
            prevout_script()
        {
        }
        
        serializer::transaction transaction;
        serializer::ec_private ec_private_key;
        serializer::base16 nonce;
        serializer::script prevout_script;
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
            sighash()
        {
        }
        
        bool help;
        size_t index;
        serializer::hashtype sighash;
    } option_;
};

} // extension
} // sx

#endif
