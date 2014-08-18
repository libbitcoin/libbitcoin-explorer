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
#ifndef SX_TX_ENCODE_HPP
#define SX_TX_ENCODE_HPP

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
#define SX_TX_ENCODE_LOCKTIME_CONFLICT \
    "Lock time is ineffective if set but all sequences are set to the maximum value."

/**
 * Class to implement the sx tx-encode command.
 */
class tx_encode 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "tx-encode"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return tx_encode::symbol();
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
                SX_VARIABLE_CONFIG ",c",
                value<boost::filesystem::path>(),                 
                "The path and file name for the configuration settings file for this application."
            )
            (
                "help,h",
                value<bool>(&option_.help)->implicit_value(true),
                "Encode an unsigned transaction."
            )
            (
                "lock_time,l",
                value<uint32_t>(&option_.lock_time),
                "The transaction lock time."
            )
            (
                "version,v",
                value<uint32_t>(&option_.version)->default_value(1),
                "The transaction version."
            )
            (
                "input,i",
                value<std::vector<serializer::input>>(&option_.inputs),
                "The set of transaction input points encoded as TXHASH:INDEX:SEQUENCE. TXHASH is a Base16 transaction hash. INDEX is the 32 bit input index in the context of the transaction. SEQUENCE the optional 32 bit input sequence and defaults to the maximum value."
            )
            (
                "output,o",
                value<std::vector<serializer::output>>(&option_.outputs),
                "The set of transaction output data encoded as TARGET:SATOSHI:SEED. TARGET is an address (including stealth or pay-to-script-hash) or a Base16 script. SATOSHI is the 32 bit spend amount in satoshi. SEED is required for stealth outputs and not used otherwise. A seed should NOT be used for multiple outputs."
            )
            (
                "TRANSACTION",
                value<std::string>(&argument_.transaction),
                "The encoded transaction file path. If not specified the transaction is written to STDOUT."
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
    virtual std::string& get_transaction_argument()
    {
        return argument_.transaction;
    }
    
    /**
     * Set the value of the TRANSACTION argument.
     */
    virtual void set_transaction_argument(
        const std::string& value)
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
     * Get the value of the lock_time option.
     */
    virtual uint32_t& get_lock_time_option()
    {
        return option_.lock_time;
    }
    
    /**
     * Set the value of the lock_time option.
     */
    virtual void set_lock_time_option(
        const uint32_t& value)
    {
        option_.lock_time = value;
    }

    /**
     * Get the value of the version option.
     */
    virtual uint32_t& get_version_option()
    {
        return option_.version;
    }
    
    /**
     * Set the value of the version option.
     */
    virtual void set_version_option(
        const uint32_t& value)
    {
        option_.version = value;
    }

    /**
     * Get the value of the input options.
     */
    virtual std::vector<serializer::input>& get_inputs_option()
    {
        return option_.inputs;
    }
    
    /**
     * Set the value of the input options.
     */
    virtual void set_inputs_option(
        const std::vector<serializer::input>& value)
    {
        option_.inputs = value;
    }

    /**
     * Get the value of the output options.
     */
    virtual std::vector<serializer::output>& get_outputs_option()
    {
        return option_.outputs;
    }
    
    /**
     * Set the value of the output options.
     */
    virtual void set_outputs_option(
        const std::vector<serializer::output>& value)
    {
        option_.outputs = value;
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
          : transaction()
        {
        }
        
        std::string transaction;
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
            lock_time(),
            version(),
            inputs(),
            outputs()
        {
        }
        
        bool help;
        uint32_t lock_time;
        uint32_t version;
        std::vector<serializer::input> inputs;
        std::vector<serializer::output> outputs;
    } option_;
};

} // extension
} // sx

#endif
