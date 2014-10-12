/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#ifndef BX_INPUT_VALIDATE_HPP
#define BX_INPUT_VALIDATE_HPP

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
#define BX_INPUT_VALIDATE_INDEX_OUT_OF_RANGE \
    "The index does not refer to an existing input."
#define BX_INPUT_VALIDATE_INDEX_VALID_SIGNATURE \
    "The signature is valid."
#define BX_INPUT_VALIDATE_INDEX_INVALID_SIGNATURE \
    "The signature is not valid."

/**
 * Class to implement the input-validate command.
 */
class input_validate 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "input-validate"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return input_validate::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "TRANSACTION";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Validate a transaction signature.";
    }    

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("EC_PUBLIC_KEY", 1)
            .add("PREVOUT_SCRIPT", 1)
            .add("SIGNATURE", 1)
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
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    virtual options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
        (
            BX_HELP_VARIABLE ",h",
            value<bool>()->zero_tokens(),
            "Get a description and instructions for this command."
        )
        (
            BX_CONFIG_VARIABLE ",c",
            value<boost::filesystem::path>(),
            "The path to the configuration settings file."
        )
        (
            "index,i",
            value<size_t>(&option_.index),
            "The ordinal position of the input within the transaction, defaults to zero."
        )
        (
            "signature_type,s",
            value<primitives::hashtype>(&option_.signature_type),
            "A token that indicates how the transaction was hashed for signing. Options are 'all', 'none', 'single', or 'anyone_can_pay', defaults to 'single'."
        )
        (
            "EC_PUBLIC_KEY",
            value<primitives::ec_public>(&argument_.ec_public_key)->required(),
            "The Base16 EC public key to verify against."
        )
        (
            "PREVOUT_SCRIPT",
            value<primitives::script>(&argument_.prevout_script)->required(),
            "The previous output script used in signing."
        )
        (
            "SIGNATURE",
            value<primitives::base16>(&argument_.signature)->required(),
            "The Base16 signature to validate."
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
     * Get the value of the EC_PUBLIC_KEY argument.
     */
    virtual primitives::ec_public& get_ec_public_key_argument()
    {
        return argument_.ec_public_key;
    }

    /**
     * Set the value of the EC_PUBLIC_KEY argument.
     */
    virtual void set_ec_public_key_argument(
        const primitives::ec_public& value)
    {
        argument_.ec_public_key = value;
    }

    /**
     * Get the value of the PREVOUT_SCRIPT argument.
     */
    virtual primitives::script& get_prevout_script_argument()
    {
        return argument_.prevout_script;
    }

    /**
     * Set the value of the PREVOUT_SCRIPT argument.
     */
    virtual void set_prevout_script_argument(
        const primitives::script& value)
    {
        argument_.prevout_script = value;
    }

    /**
     * Get the value of the SIGNATURE argument.
     */
    virtual primitives::base16& get_signature_argument()
    {
        return argument_.signature;
    }

    /**
     * Set the value of the SIGNATURE argument.
     */
    virtual void set_signature_argument(
        const primitives::base16& value)
    {
        argument_.signature = value;
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
          : ec_public_key(),
            prevout_script(),
            signature(),
            transaction()
        {
        }

        primitives::ec_public ec_public_key;
        primitives::script prevout_script;
        primitives::base16 signature;
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
          : index(),
            signature_type()
        {
        }

        size_t index;
        primitives::hashtype signature_type;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
