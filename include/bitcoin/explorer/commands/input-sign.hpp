/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BX_INPUT_SIGN_HPP
#define BX_INPUT_SIGN_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/generated.hpp>
#include <bitcoin/explorer/config/address.hpp>
#include <bitcoin/explorer/config/algorithm.hpp>
#include <bitcoin/explorer/config/btc.hpp>
#include <bitcoin/explorer/config/byte.hpp>
#include <bitcoin/explorer/config/cert_key.hpp>
#include <bitcoin/explorer/config/ec_private.hpp>
#include <bitcoin/explorer/config/electrum.hpp>
#include <bitcoin/explorer/config/encoding.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/hashtype.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/raw.hpp>
#include <bitcoin/explorer/config/signature.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_INPUT_SIGN_INDEX_OUT_OF_RANGE \
    "The index does not refer to an existing input."
#define BX_INPUT_SIGN_FAILED \
    "The signing operation failed."

/**
 * Class to implement the input-sign command.
 */
class BCX_API input_sign
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "input-sign";
    }

    /**
     * The symbolic (not localizable) former command name, lower case.
     */
    static const char* formerly()
    {
        return "sign-input";
    }

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
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Create an endorsement for a transaction input.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("EC_PRIVATE_KEY", 1)
            .add("CONTRACT", 1)
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
        const auto raw = requires_raw_input();
        load_input(get_transaction_argument(), "TRANSACTION", variables, input, raw);
    }

    /**
     * Load program option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    virtual system::options_metadata& load_options()
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
            "anyone,a",
            value<bool>(&option_.anyone)->zero_tokens(),
            "Modify signature hashing so that other inputs are ignored."
        )
        (
            "index,i",
            value<uint32_t>(&option_.index),
            "The ordinal position of the input within the transaction, defaults to 0."
        )
        (
            "sign_type,s",
            value<explorer::config::hashtype>(&option_.sign_type),
            "A token that indicates how the transaction should be hashed for signing. Options are 'all', 'none', and 'single', defaults to 'all'."
        )
        (
            "EC_PRIVATE_KEY",
            value<explorer::config::ec_private>(&argument_.ec_private_key)->required(),
            "The Base16 EC private key to sign with."
        )
        (
            "CONTRACT",
            value<system::config::script>(&argument_.contract)->required(),
            "The previous output script to use in signing. Multiple tokens must be quoted."
        )
        (
            "TRANSACTION",
            value<system::config::transaction>(&argument_.transaction),
            "The Base16 transaction. If not specified the transaction is read from STDIN."
        );

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual system::console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the EC_PRIVATE_KEY argument.
     */
    virtual explorer::config::ec_private& get_ec_private_key_argument()
    {
        return argument_.ec_private_key;
    }

    /**
     * Set the value of the EC_PRIVATE_KEY argument.
     */
    virtual void set_ec_private_key_argument(
        const explorer::config::ec_private& value)
    {
        argument_.ec_private_key = value;
    }

    /**
     * Get the value of the CONTRACT argument.
     */
    virtual system::config::script& get_contract_argument()
    {
        return argument_.contract;
    }

    /**
     * Set the value of the CONTRACT argument.
     */
    virtual void set_contract_argument(
        const system::config::script& value)
    {
        argument_.contract = value;
    }

    /**
     * Get the value of the TRANSACTION argument.
     */
    virtual system::config::transaction& get_transaction_argument()
    {
        return argument_.transaction;
    }

    /**
     * Set the value of the TRANSACTION argument.
     */
    virtual void set_transaction_argument(
        const system::config::transaction& value)
    {
        argument_.transaction = value;
    }

    /**
     * Get the value of the anyone option.
     */
    virtual bool& get_anyone_option()
    {
        return option_.anyone;
    }

    /**
     * Set the value of the anyone option.
     */
    virtual void set_anyone_option(
        const bool& value)
    {
        option_.anyone = value;
    }

    /**
     * Get the value of the index option.
     */
    virtual uint32_t& get_index_option()
    {
        return option_.index;
    }

    /**
     * Set the value of the index option.
     */
    virtual void set_index_option(
        const uint32_t& value)
    {
        option_.index = value;
    }

    /**
     * Get the value of the sign_type option.
     */
    virtual explorer::config::hashtype& get_sign_type_option()
    {
        return option_.sign_type;
    }

    /**
     * Set the value of the sign_type option.
     */
    virtual void set_sign_type_option(
        const explorer::config::hashtype& value)
    {
        option_.sign_type = value;
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
            contract(),
            transaction()
        {
        }

        explorer::config::ec_private ec_private_key;
        system::config::script contract;
        system::config::transaction transaction;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : anyone(),
            index(),
            sign_type()
        {
        }

        bool anyone;
        uint32_t index;
        explorer::config::hashtype sign_type;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
