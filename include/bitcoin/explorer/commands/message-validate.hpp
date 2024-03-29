/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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
#ifndef BX_MESSAGE_VALIDATE_HPP
#define BX_MESSAGE_VALIDATE_HPP

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
#define BX_MESSAGE_VALIDATE_INDEX_VALID_SIGNATURE \
    "The signature is valid."
#define BX_MESSAGE_VALIDATE_INDEX_INVALID_SIGNATURE \
    "The signature is not valid."

/**
 * Class to implement the message-validate command.
 */
class BCX_API message_validate
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "message-validate";
    }

    /**
     * Destructor.
     */
    virtual ~message_validate()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return message_validate::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "MESSAGING";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Validate a message signature.";
    }

    /**
     * Determines if STDIN is required to be raw.
     * @return  True if the type of the STDIN argument is primitive::raw.
     */
    virtual bool requires_raw_input()
    {
        return true;
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("PAYMENT_ADDRESS", 1)
            .add("SIGNATURE", 1)
            .add("MESSAGE", 1);
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
        load_input(get_message_argument(), "MESSAGE", variables, input, raw);
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
            "PAYMENT_ADDRESS",
            value<system::wallet::payment_address>(&argument_.payment_address)->required(),
            "The payment address of the message signer."
        )
        (
            "SIGNATURE",
            value<explorer::config::signature>(&argument_.signature)->required(),
            "The message signature."
        )
        (
            "MESSAGE",
            value<explorer::config::bytes>(&argument_.message),
            "The binary message data for which the signature applies. If not specified the message is read from STDIN."
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
     * Get the value of the PAYMENT_ADDRESS argument.
     */
    virtual system::wallet::payment_address& get_payment_address_argument()
    {
        return argument_.payment_address;
    }

    /**
     * Set the value of the PAYMENT_ADDRESS argument.
     */
    virtual void set_payment_address_argument(
        const system::wallet::payment_address& value)
    {
        argument_.payment_address = value;
    }

    /**
     * Get the value of the SIGNATURE argument.
     */
    virtual explorer::config::signature& get_signature_argument()
    {
        return argument_.signature;
    }

    /**
     * Set the value of the SIGNATURE argument.
     */
    virtual void set_signature_argument(
        const explorer::config::signature& value)
    {
        argument_.signature = value;
    }

    /**
     * Get the value of the MESSAGE argument.
     */
    virtual explorer::config::bytes& get_message_argument()
    {
        return argument_.message;
    }

    /**
     * Set the value of the MESSAGE argument.
     */
    virtual void set_message_argument(
        const explorer::config::bytes& value)
    {
        argument_.message = value;
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
          : payment_address(),
            signature(),
            message()
        {
        }

        system::wallet::payment_address payment_address;
        explorer::config::signature signature;
        explorer::config::bytes message;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
        {
        }

    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
