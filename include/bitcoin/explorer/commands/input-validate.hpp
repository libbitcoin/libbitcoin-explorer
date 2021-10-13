/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
#ifndef BX_INPUT_VALIDATE_HPP
#define BX_INPUT_VALIDATE_HPP

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
#include <bitcoin/explorer/config/bytes.hpp>
#include <bitcoin/explorer/config/electrum.hpp>
#include <bitcoin/explorer/config/encoding.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/sighash.hpp>
#include <bitcoin/explorer/config/signature.hpp>
#include <bitcoin/explorer/config/witness.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>
#include <bitcoin/protocol/zmq/sodium.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_INPUT_VALIDATE_INDEX_OUT_OF_RANGE \
    "The index does not refer to an existing input."
#define BX_INPUT_VALIDATE_INDEX_VALID_ENDORSEMENT \
    "The endorsement is valid."
#define BX_INPUT_VALIDATE_INDEX_INVALID_ENDORSEMENT \
    "The endorsement is not valid."

/**
 * Class to implement the input-validate command.
 */
class BCX_API input_validate
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "input-validate";
    }

    /**
     * The symbolic (not localizable) former command name, lower case.
     */
    static const char* formerly()
    {
        return "validsig";
    }

    /**
     * Destructor.
     */
    virtual ~input_validate()
    {
    }

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
        return "Validate a transaction input endorsement.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("EC_PUBLIC_KEY", 1)
            .add("CONTRACT", 1)
            .add("ENDORSEMENT", 1)
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
            "index,i",
            value<uint32_t>(&option_.index),
            "The ordinal position of the input within the transaction, defaults to 0."
        )
        (
            "EC_PUBLIC_KEY",
            value<system::wallet::ec_public>(&argument_.ec_public_key)->required(),
            "The Base16 EC public key to verify against."
        )
        (
            "CONTRACT",
            value<system::config::script>(&argument_.contract)->required(),
            "The previous output script used in signing. Multiple tokens must be quoted."
        )
        (
            "ENDORSEMENT",
            value<explorer::config::endorsement>(&argument_.endorsement)->required(),
            "The endorsement to validate."
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
     * Get the value of the EC_PUBLIC_KEY argument.
     */
    virtual system::wallet::ec_public& get_ec_public_key_argument()
    {
        return argument_.ec_public_key;
    }

    /**
     * Set the value of the EC_PUBLIC_KEY argument.
     */
    virtual void set_ec_public_key_argument(
        const system::wallet::ec_public& value)
    {
        argument_.ec_public_key = value;
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
     * Get the value of the ENDORSEMENT argument.
     */
    virtual explorer::config::endorsement& get_endorsement_argument()
    {
        return argument_.endorsement;
    }

    /**
     * Set the value of the ENDORSEMENT argument.
     */
    virtual void set_endorsement_argument(
        const explorer::config::endorsement& value)
    {
        argument_.endorsement = value;
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
            contract(),
            endorsement(),
            transaction()
        {
        }

        system::wallet::ec_public ec_public_key;
        system::config::script contract;
        explorer::config::endorsement endorsement;
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
          : index()
        {
        }

        uint32_t index;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
